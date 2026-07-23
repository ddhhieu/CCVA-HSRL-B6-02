#  Dự Án CCVA-HSRL-B6-02

[![GitHub License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Repo Status](https://img.shields.io/badge/Status-In_Progress-orange.svg)]()
[![Team](https://img.shields.io/badge/Team-B6--02-brightgreen.svg)]()



##  Giới Thiệu Dự Án

Dự án **CCVA-HSRL-B6-02** phát triển robot tự hành trên nền tảng MATRIX Mini R4, sử dụng bộ công cụ MATRIX WRO Future Innovators Set V2. Robot thực hiện nhiệm vụ di chuyển theo luật thi đấu bảng B6 - WRO 2026 với hai vòng thi Open Challenge và Obstacle Challenge, sử dụng laser sensor V2, color sensor V3 và M-vision camera.
##  Giới Thiệu Đội Nhóm (Team B6-02)

Nhóm **B6-02** bao gồm các thành viên sau 

| STT | Họ và tên | Vai trò | GitHub |
|:---:|:----------|:--------|:-------|
| 1 | Đào Đức Hiếu  | Leader / Repository Maintainer | [@ddhhieu](https://github.com/ddhhieu) |
| 2 | Huy Nguyễn | Developer / Technical Specialist | [@huynguyen123qn6-prog](https://github.com/huynguyen123qn6-prog) |
| 3 | Quang Tùng | Developer / Tester | — |

## Mục tiêu chính: ##
- Xây dựng robot tự hành trên nền tảng MATRIX Mini R4 đáp ứng luật thi bảng B6 - WRO 2026.
- Hoàn thành vòng **Open Challenge**: bám tường ổn định bằng laser sensor V2 với bộ điều khiển PID, xác định chiều chạy qua color sensor V3, chạy đủ 3 vòng sân.
- Hoàn thành vòng **Obstacle Challenge**: nhận diện khối đỏ/xanh bằng M-vision camera và điều hướng tránh vật theo đúng quy tắc.
- Đảm bảo tính lặp lại và ổn định của robot qua nhiều lượt chạy thử nghiệm.
- Xây dựng bộ tài liệu kỹ thuật đầy đủ: hướng dẫn lắp ráp, mã nguồn có chú thích, hình ảnh và video minh họa.  
---

## Hệ Thống Phần Cứng

Để đạt các mục tiêu trên, robot cần đo được khoảng cách tới tường, nhận biết vạch màu trên sân và phát hiện khối màu. Nhóm sử dụng các thiết bị có sẵn trong bộ MATRIX WRO Future Innovators Set V2:

### Cảm biến

| Thiết bị | SL | Chức năng |
|:---------|:--:|:----------|
| Laser sensor V2 | 2 | Đo khoảng cách tới tường hai bên, dùng cho thuật toán bám tường |
| Color sensor V3 | 1 | Nhận biết vạch màu trên sân để xác định chiều chạy và đếm vòng |
| M-vision camera | 1 | Nhận diện khối màu đỏ / xanh trong vòng Obstacle Challenge |

### Cơ cấu chấp hành

| Thiết bị | Chức năng |
|:---------|:----------|
| Động cơ DC | Truyền động di chuyển, encoder đo quãng đường |
| Servo | Điều khiển góc lái |

### Bộ điều khiển

**MATRIX Mini R4** — đọc dữ liệu cảm biến, chạy vòng điều khiển PID, nhận tín hiệu từ camera và điều khiển động cơ.
## Hướng dẫn sử dụng

### 1. Chuẩn bị môi trường vận hành 

**Cài đặt Arduino IDE**

Truy cập trang tài nguyên của MATRIX Robotics để tải Arduino IDE và thư viện MATRIX Mini R4:
https://www.matrixrobotics.com/adv-program-resources

**Cài đặt OpenMV IDE**

Sau khi cài đặt Arduino IDE, tiếp tục cài đặt OpenMV IDE để lập trình cho camera OpenMV.
Hướng dẫn cài đặt:

https://wro-learn.org/en_us/wiki/m-vision-camera

### 2. Tải dự án về máy

**Cách 1: Dùng Git**

Mở terminal tại thư mục muốn lưu dự án, chạy:

```bash
git clone https://github.com/ddhhieu/CCVA-HSRL-B6-02.git
```
**Cách 2: Tải ZIP** (không cần cài Git)

Vào https://github.com/ddhhieu/CCVA-HSRL-B6-02 → bấm **Code** → **Download ZIP** → giải nén.

### 3. Lắp ráp robot

Thực hiện theo hướng dẫn lắp ráp chi tiết:

[Slide lắp ráp (PDF)](https://github.com/ddhhieu/CCVA-HSRL-B6-02/blob/main/Slide%20l%E1%BA%AFp%20r%C3%A1p.pdf)

### 4. Nạp chương trình cho MATRIX Mini R4

**4.1. Cài đặt thư viện**

Trước khi nạp, đảm bảo đã cài đủ các thư viện sau trong Arduino IDE:

| Thư viện | Cách cài |
|:---------|:---------|
| Matrix Mini R4 | Tải từ [MATRIX Robotics](https://www.matrixrobotics.com/adv-program-resources) → **Sketch → Include Library → Add .ZIP Library...** |
| `MiniR4SmartCamReader.h` | Copy thủ công vào `Documents/Arduino/libraries/Matrix Mini R4/src/module/sensor/` |

**4.2. Mở mã nguồn**

Mở Arduino IDE → **File → Open...**

**4.3. Cấu hình board**

- **Tools → Board** → chọn board tương ứng với MATRIX Mini R4
- **Tools → Port** → chọn cổng COM mà robot đang kết nối

**4.4. Biên dịch và nạp**

- Bấm **Verify** (✓) để biên dịch, kiểm tra không có lỗi
- Bấm **Upload** (→) để nạp chương trình vào robot
- Chờ tới khi hiện thông báo `Done uploading`

>  Nếu Arduino IDE báo `No such file or directory`, kiểm tra lại xem đã cài đủ thư viện ở bước 4.1 chưa.
     
## API các hàm điều khiển 

### Vòng 1 Open Challenge 
Các tham số được cài đặt trong `loop()`.
#### Bám tường phải
```cpp
void Di_line_phai_voi_toc_do_n_quang_duong_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(
    float speed, float cm, float Kp, float Ki, float Kd, float mm);
```

| Tham số | Đơn vị | Mô tả |
|:--------|:-------|:------|
| `speed` | — | Tốc độ di chuyển |
| `cm` | cm | Quãng đường cần đi |
| `Kp`, `Ki`, `Kd` | — | Hệ số bộ điều khiển PID |
| `mm` | mm | Khoảng cách mong muốn tới tường |

#### Bám tường trái

```cpp
void Di_line_trai_toc_do_n_cm_n_Kp_n_Ki_n_Kd_n_cach_tuong_n(
    float toc_do, float cm, float Kp, float Ki, float Kd, float mm);
```

Tham số tương tự bám tường phải.

#### Đi giữa hai tường

```cpp
void Di_line_giua_voi_toc_do_n_quang_duong_n_Kp_n_Ki_n_Kd_n(
    float toc_do_giua, float cm_giua, float Kp, float Ki, float Kd);
```

| Tham số | Đơn vị | Mô tả |
|:--------|:-------|:------|
| `toc_do_giua` | — | Tốc độ di chuyển |
| `cm_giua` | cm | Quãng đường cần đi |
| `Kp`, `Ki`, `Kd` | — | Hệ số PID (sai lệch = hiệu khoảng cách hai bên) |

#### Đi thẳng không bám tường

```cpp
void Di_mu_n_voi_toc_do_n(float cm, float speed);
```

| Tham số | Đơn vị | Mô tả |
|:--------|:-------|:------|
| `cm` | cm | Quãng đường cần đi |
| `speed` | — | Tốc độ di chuyển |

##### Kịch bản chạy vòng 1

```cpp
void Di_cung_chieu_kim_dong_ho();   // Chạy thuận chiều kim đồng hồ
void DiNguocChieuKimDongHo();       // Chạy ngược chiều kim đồng hồ
```
---
### Vòng 2 — Obstacle Challenge

Robot chạy 3 vòng quanh sa bàn. Trên đường có các khối màu:

- **Khối đỏ** → robot đi vòng qua bên phải khối
- **Khối xanh lá** → robot đi vòng qua bên trái khối

Không được đụng làm khối đổ hay lệch chỗ.

Để làm được, robot dùng 3 cảm biến:

- **Laser** đo khoảng cách tới tường → giữ xe chạy giữa làn, không đâm tường
- **Camera** nhìn thấy khối màu gì, ở đâu → quyết định né trái hay né phải
- **Cảm biến màu** đọc vạch dưới sàn → đếm đủ 3 vòng thì dừng

#### Robot cần làm những việc gì

**1. Bám tường** — Đọc laser, tính xem xe đang cách tường bao nhiêu, rồi bẻ lái
cho xe về đúng khoảng cách mong muốn. Chạy liên tục suốt lượt.

**2. Né khối** — Hỏi camera xem có khối không. Nếu có khối đủ gần thì:
khối đỏ bẻ lái sang trái, khối xanh bẻ lái sang phải.
Khối càng lệch khỏi giữa khung hình thì bẻ lái càng gắt.

**3. Đếm vòng** — Đọc cảm biến màu. Mỗi lần đi qua vạch cam hoặc xanh dương
thì cộng 1. Đếm đủ 12 vạch là xong 3 vòng, cho xe dừng.

**4. Qua góc sa bàn** — Khi tới góc, xe phải rẽ, đồng thời quét camera xem
đoạn tiếp theo có khối nào không.

#### Giao tiếp với camera

Mini R4 hỏi trước, camera trả lời sau. Camera không tự gửi gì cả.

Mini R4 gửi 1 chữ cái:

- **`'G'`** → camera chụp ảnh, tìm khối, gửi về 4 số
- **`'L'`** → camera bật đèn LED xanh (kiểm tra kết nối), không gửi gì về

4 số camera gửi về được lưu vào mảng `camData[]`:

| Vị trí | Ý nghĩa |
|:------:|:--------|
| `camData[0]` | Màu khối: `0` đỏ, `1` xanh, `255` không thấy |
| `camData[1]` | Vị trí ngang trong khung hình (0–320, giữa là 160) |
| `camData[2]` | Vị trí dọc (càng lớn = khối càng gần robot) |
| `camData[3]` | Diện tích khối — hiện chưa dùng |

Khung hình QVGA 320 × 240 pixel, gốc tọa độ ở góc trên trái.

**Ví dụ xử lý:**

```cpp
if (camData[2] > Y_IGNOR) {      // Chỉ xử lý khối đủ gần
    if (camData[0] == 0) {
        // Khối đỏ → tránh sang trái
    }
    else if (camData[0] == 1) {
        // Khối xanh → tránh sang phải
    }
}
```

#### Hằng số cấu hình

| Hằng số | Giá trị | Ý nghĩa |
|:--------|:-------:|:--------|
| `Y_IGNOR` | 50 | Khối có `camData[2]` nhỏ hơn giá trị này là ở quá xa, bỏ qua |
| `DOOR` | 12 | Số vạch màu cần đếm để kết thúc lượt chạy |
| `d` | 19.6 | Chu vi bánh xe (cm), quy đổi góc encoder sang quãng đường |

#### Các hàm chính

**Giới hạn giá trị**

```cpp
float limit(float value, float min, float max);
```

Kẹp `value` trong khoảng `[min, max]`. Dùng trước khi điều khiển góc lái.

**Điều khiển servo lái**

```cpp
void servoMotor(float value, float l = 70);
```

| Tham số | Đơn vị | Mô tả |
|:--------|:-------|:------|
| `value` | độ | Góc muốn xoay (`0` = đi thẳng, âm = trái, dương = phải) |
| `l` | độ | Giới hạn góc xoay tối đa, mặc định 70 |

## License

Dự án được phát hành theo giấy phép [MIT](LICENSE).

.


 
