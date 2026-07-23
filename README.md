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

Robot bám tường bằng laser sensor, đếm vòng bằng color sensor và nhận diện khối màu bằng M-vision camera.

#### Hằng số cấu hình

| Hằng số | Giá trị | Ý nghĩa |
|:--------|:-------:|:--------|
| `Y_IGNOR` | 50 | Ngưỡng tọa độ Y tối thiểu để xử lý khối. Khối ở xa hơn sẽ bị bỏ qua |
| `DOOR` | 12 | Số vạch màu cần đếm để kết thúc lượt chạy |
| `d` | 19.6 | Chu vi bánh xe (cm), dùng quy đổi góc encoder sang quãng đường |

#### Giới hạn giá trị

```cpp
float limit(float value, float min, float max);
```

| Tham số | Đơn vị | Mô tả |
|:--------|:-------|:------|
| `value` | — | Giá trị cần giới hạn |
| `min` | — | Cận dưới |
| `max` | — | Cận trên |

Trả về giá trị đã được kẹp trong khoảng `[min, max]`, dùng trước khi điều khiển góc lái.

#### Điều khiển servo lái

```cpp
void servoMotor(float value, float l = 70);
```

| Tham số | Đơn vị | Mô tả |
|:--------|:-------|:------|
| `value` | độ | Góc muốn xoay (`0` = đi thẳng) |
| `l` | độ | Giới hạn góc xoay tối đa, mặc định 70 |


#### Đếm vạch màu

```cpp
void line_check();
```

Đọc color sensor, tăng biến đếm khi robot đi qua vạch xanh hoặc cam. Có kiểm tra quãng đường tối thiểu giữa hai lần đếm để tránh đếm trùng.

#### Xử lý góc sa bàn

```cpp
bool turn();
```

Khi robot tới góc sa bàn, thực hiện quét camera tìm khối tiếp theo và điều chỉnh hướng di chuyển. Trả về `true` nếu đã tới góc sa bàn.

#### Di chuyển theo quãng đường

```cpp
bool dichuyen_cm(float quang_duong);
```
| Tham số | Đơn vị | Mô tả |
|:--------|:-------|:------|
| `quang_duong` | cm | Quãng đường cần di chuyển, đo bằng encoder |

Trả về `false` nếu bị ngắt giữa chừng do gặp góc sa bàn.

## License

Dự án được phát hành theo giấy phép [MIT](LICENSE).


 
