#  Dự Án CCVA-HSRL-B6-02

[![GitHub License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Repo Status](https://img.shields.io/badge/Status-In_Progress-orange.svg)]()
[![Team](https://img.shields.io/badge/Team-B6--02-brightgreen.svg)]()

Chào mừng bạn đến với kho lưu trữ chính thức của nhóm **B6-02** thuộc dự án/môn học **CCVA-HSRL**. Nơi đây lưu trữ toàn bộ mã nguồn, tài liệu kĩ thuật, quy trình thử nghiệm và kết quả đạt được của dự án.

---
---

##  Giới Thiệu Đội Nhóm (Team B6-02)

Nhóm **B6-02** bao gồm các thành viên sau 

| STT | Họ và tên | Vai trò | GitHub |
|:---:|:----------|:--------|:-------|
| 1 | Đỗ Hoàng Hiếu | Leader / Repository Maintainer | [@ddhhieu](https://github.com/ddhhieu) |
| 2 | Huy Nguyễn | Developer / Technical Specialist | [@huynguyen123qn6-prog](https://github.com/huynguyen123qn6-prog) |
| 3 | Quang Tùng | Developer / Tester | — |


##  Giới Thiệu Dự Án

Dự án **CCVA-HSRL-B6-02** tập trung nghiên cứu, phát triển và triển khai các giải pháp phần mềm/mô hình ứng dụng đáp ứng yêu cầu của chuỗi dự án CCVA-HSRL.

* **Mục tiêu chính:**
  

---


# 1. Tải dự án về máy
[https://github.com/ddhhieu/CCVA-HSRL-B6-02.git](https://github.com/ddhhieu/CCVA-HSRL-B6-02.git)
```cpp
cd CCVA-HSRL-B6-02
```

 # 2. lắp ráp robot
    https://github.com/ddhhieu/CCVA-HSRL-B6-02/blob/main/Slide%20l%E1%BA%AFp%20r%C3%A1p.pdf

    

 # 3 .code
     https://github.com/ddhhieu/CCVA-HSRL-B6-02/tree/main/CCVA-HSRL-B6-02

     
     
 # 4. openmv
       https://github.com/ddhhieu/CCVA-HSRL-B6-02/tree/main/CCVA-HSRL-B6-02

       
# CÁC HÀM CHÍNH 
## API các hàm điều khiển

### Vòng 1

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

#### Kịch bản chạy vòng 1

```cpp
void Di_cung_chieu_kim_dong_ho();   // Chạy thuận chiều kim đồng hồ
void DiNguocChieuKimDongHo();       // Chạy ngược chiều kim đồng hồ
```

---

## Hiệu chỉnh PID

| Hệ số | Tăng quá mức | Giảm quá mức |
|:------|:-------------|:-------------|
| `Kp` | Dao động quanh tường | Phản ứng chậm, lệch xa |
| `Ki` | Overshoot, mất ổn định | Sai số xác lập không triệt tiêu |
| `Kd` | Nhạy nhiễu cảm biến | Rung khi vào cua |

Quy trình khuyến nghị: tăng `Kp` đến khi bắt đầu dao động → thêm `Kd` để dập dao động → thêm `Ki` nếu còn sai số xác lập.

---

## License




 
