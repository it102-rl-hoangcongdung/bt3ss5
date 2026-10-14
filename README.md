# BÁO CÁO BÀI TẬP 03: PHÂN TÍCH TRADE-OFF MẢNG TĨNH VÀ QUẢN LÝ HÀNG CHỜ PHÒNG KHÁM

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Activity Diagram)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt3.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  Start([Bắt đầu]) --> InputN[Nhập số lượng bệnh nhân n ban đầu]
  InputN --> CheckN{0 <= n <= 100?}
  CheckN -- Không hợp lệ --> ErrN[Thông báo lỗi & Nhập lại] --> InputN
  CheckN -- Hợp lệ --> InputData[Vòng lặp nhập: Mã, Tuổi, BHYT]
  InputData --> ValidateAge{1 <= Tuổi <= 120?}
  ValidateAge -- Sai --> ErrAge[Báo lỗi tuổi & Yêu cầu nhập lại] --> InputData
  ValidateAge -- Đúng --> ValidateHI{BHYT == 0 hoặc 1?}
  ValidateHI -- Sai --> ErrHI[Báo lỗi BHYT & Nhập lại] --> InputData
  ValidateHI -- Đúng --> CalcFee[Tính phí: Nếu BHYT=1 -> 30k, BHYT=0 -> 150k]
  CalcFee --> SaveQueue[Lưu vào mảng hàng chờ active]
  SaveQueue --> DisplayQueue[In danh sách hàng chờ, tổng doanh thu & số lượng ưu tiên]
  DisplayQueue --> AskCancel{Có bệnh nhân hủy lượt khám?}
  AskCancel -- Không --> End([Kết thúc phiên làm việc])
  AskCancel -- Có --> InputK[Nhập chỉ số vị trí K cần hủy]
  InputK --> CheckK{0 <= K < n và n > 0?}
  CheckK -- Không hợp lệ --> ErrK[Thông báo lỗi vị trí K không tồn tại] --> End
  CheckK -- Hợp lệ --> ShiftArray[Thực hiện dồn dịch mảng: arr[i] = arr[i+1]]
  ShiftArray --> UpdateN[Giảm n đi 1: n = n - 1]
  UpdateN --> Recompute[Cập nhật lại tổng doanh thu dự kiến]
  Recompute --> DisplayNew[In danh sách hàng chờ mới & doanh thu cập nhật] --> End
```

---

## Nhiệm vụ 1: Phân tích các giải pháp xử lý thao tác Hủy lượt khám trên mảng 1 chiều

Bài toán đặt ra yêu cầu quản lý hàng chờ khám bệnh tối đa 100 bệnh nhân tại Phòng khám MediCare. Khi xảy ra sự cố bệnh nhân hủy lượt khám tại vị trí chỉ số K, phần mềm cũ không đồng bộ dữ liệu dẫn đến gọi khống số thứ tự và sai lệch doanh thu.

Để giải quyết triệt để vấn đề này, dưới góc độ lập trình C, chúng ta tiến hành khảo sát và đánh giá 3 giải pháp kỹ thuật khác nhau nhằm tìm ra phương án tối ưu nhất.

- Giải pháp 1: Dồn dịch mảng (Shift Array / Hard Delete). Khi phần tử tại vị trí K bị hủy, vòng lặp tiến hành kéo toàn bộ các phần tử từ chỉ số K + 1 đến n - 1 sang trái một ô. Giảm biến đếm n đi một đơn vị.
- Giải pháp 2: Đánh dấu trạng thái (Soft Delete / Lazy Deletion). Thêm một trường trạng thái 'active/inactive' cho mỗi bệnh nhân. Khi hủy, chỉ cần gán cờ thành 'inactive' mà không dịch chuyển dữ liệu.
- Giải pháp 3: Đổi chỗ phần tử cuối (Swap with Last). Lấy phần tử cuối cùng của mảng gán đè vào vị trí K, sau đó giảm n đi một đơn vị để loại bỏ phần tử cuối.

## Nhiệm vụ 2: So sánh & Lựa chọn giải pháp tối ưu

Tiến hành lập bảng so sánh chi tiết các chỉ tiêu kỹ thuật giữa ba giải pháp để đưa ra quyết định phù hợp nhất cho Kiosk phòng khám.

| Tiêu chí | Giải pháp 1: Dồn dịch mảng | Giải pháp 2: Soft Delete | Giải pháp 3: Swap với phần tử cuối |
| --- | --- | --- | --- |
| Độ phức tạp thời gian (Time Complexity) | O(n) do phải dịch chuyển tối đa n phần tử | O(1) chỉ cập nhật cờ trạng thái | O(1) hoán đổi trực tiếp giá trị |
| Bộ nhớ (Space Complexity) | O(MAX) tối ưu, không tốn thêm cờ | O(MAX) tốn thêm bộ nhớ cho cờ trạng thái | O(MAX) tối ưu bộ nhớ |
| Tính bảo toàn thứ tự FIFO | Tuyệt đối bảo toàn thứ tự gọi khám chuẩn | Bị phá vỡ nếu không lọc kỹ các bản ghi inactive | Bị xáo trộn thứ tự cấp số thứ tự ban đầu |
| Độ phức tạp cài đặt | Đơn giản, trực quan bằng vòng lặp cơ bản | Trung bình, cần xử lý logic lọc khi hiển thị | Đơn giản nhưng làm đảo lộn thứ tự hàng chờ |

## Lựa chọn giải pháp tối ưu cho bài toán

Dựa trên bảng phân tích trade-off trên, Giải pháp 1 (Dồn dịch mảng / Hard Delete) được chọn làm phương án chính thức.

Lý do chọn: Hàng chờ khám bệnh yêu cầu tính chất FIFO cực kỳ nghiêm ngặt. Số thứ tự phải gọi lần lượt từ nhỏ đến lớn không được phép xáo trộn. Mặc dù độ phức tạp thời gian là O(n), nhưng với giới hạn kích thước mảng MAX = 100, phép toán dịch chuyển mảng diễn ra trong tích tắc (vài micro giây), hoàn toàn không ảnh hưởng tới hiệu năng hệ thống Kiosk. Hơn nữa, phương án này loại bỏ hoàn toàn dữ liệu rác, giúp việc tính toán doanh thu và hiển thị màn hình bác sĩ luôn chính xác tuyệt đối.

- Đảm bảo thứ tự gọi khám từ nhỏ đến lớn đúng chuẩn hàng đợi FIFO.
- Tránh tuyệt đối tình trạng rác bộ nhớ hoặc gọi khống số thứ tự.
- Dễ dàng kiểm soát tổng doanh thu bằng cách duyệt từ đầu đến n hiện tại.

## Nhiệm vụ 3: Thiết kế luồng logic và Triển khai Mã nguồn C11

Chương trình C11 được thiết kế chuẩn hóa, kiểm soát chặt chẽ các bẫy dữ liệu như tuổi không hợp lệ, mã trạng thái BHYT sai lệch, hoặc vị trí hủy K vượt quá giới hạn hàng chờ hiện tại.

- Sử dụng kiểu dữ liệu số nguyên cho tiền tệ để tránh sai số dấu phẩy động.
- Áp dụng cấu trúc mảng song song lưu trữ Mã số, Tuổi, Trạng thái BHYT và Tiền khám.
- Xây dựng đầy đủ các bước: Nhập liệu ban đầu -> In danh sách & thống kê -> Hủy vị trí K -> In kết quả sau khi cập nhật.

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt3.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt3.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `main.c`: Mã nguồn chương trình.
