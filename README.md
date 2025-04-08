# Cải Tiến Giải Thuật kNN Bằng Cấu Trúc Dữ Liệu kD-Tree

## 1. Giới thiệu

Đây là bài tập lớn môn CO2003 – Cấu trúc dữ liệu và giải thuật, yêu cầu sinh viên cải tiến giải thuật kNN bằng cách sử dụng cấu trúc dữ liệu kD-Tree.  
Bài tập này giúp sinh viên ôn lại và áp dụng thành thạo lập trình hướng đối tượng, xây dựng các cấu trúc dữ liệu cây, cũng như các thuật toán sắp xếp và tìm kiếm.

## 2. Yêu cầu đề bài

- **Cấu trúc cây k-D Tree:**  
  + Xây dựng các phương thức cơ bản:  
    - Duyệt cây (inorder, preorder, postorder) với định dạng in mỗi node theo dạng `(a1, a2, ..., an)`
    - Tính chiều cao của cây
    - Đếm số node và số node lá
    - Phương thức chèn (`insert`) một điểm vào cây (với điểm có số chiều bằng `k`)
    - Phương thức xóa (`remove`) một điểm khỏi cây (theo các quy tắc đặc biệt của cây k-D)
    - Tìm kiếm (`search`) một điểm có trong cây hay không
    - Xây dựng cây từ danh sách các điểm (`buildTree`) sử dụng thuật toán chọn trung vị theo từng chiều
    - Tìm láng giềng gần nhất (`nearestNeighbour`) và tìm k láng giềng gần nhất (`kNearestNeighbour`)

- **Thuật toán kNN dựa trên cây k-D Tree:**  
  Class `kNN` bao gồm các phương thức:
  - `fit`: Huấn luyện trên bộ dữ liệu huấn luyện (sử dụng cây k-D Tree cho các điểm trong X_train)
  - `predict`: Dự đoán nhãn cho các ảnh trong X_test dựa trên việc tìm k láng giềng gần nhất trong cây
  - `score`: Tính độ chính xác của kết quả dự đoán

- **Các lớp Dataset và hàm train_test_split:**  
  Được cung cấp sẵn và không cần thay đổi. Chúng giúp xử lý dữ liệu của bộ MNIST.

## 3. Cấu trúc dự án

```
Assignment2_KDTree_KNN/
├── include/
│   ├── kDTree.hpp          // Header của class kDTree (sinh viên được phép sửa đổi)
│   ├── main.hpp            // Các định nghĩa, macro và các khai báo cần thiết cho main (không thay đổi)
│   └── Dataset.hpp         // Class Dataset (không sửa đổi)
│
├── src/
│   ├── kDTree.cpp          // File cài đặt cho class kDTree (sinh viên được phép sửa đổi)
│   ├── main.cpp            // File main chứa testcase và hàm main (không sửa đổi)
│   └── Dataset.o           // Đã biên dịch (không sửa đổi)
│
├── data/
│   └── mnist.csv           // File dữ liệu mẫu cho bộ dữ liệu MNIST
│
└── README.md               // Hướng dẫn và giải thích cách chạy, ý nghĩa các file trong dự án


```



## 4. Hướng dẫn biên dịch và chạy chương trình

- **Biên dịch:**  
  Sử dụng dòng lệnh sau trên môi trường UNIX:
g++ -o main src/main.cpp src/kDTree.cpp src/Dataset.o -I include -std=c++11



- **Chạy chương trình:**  
  Sau khi biên dịch thành công, chạy chương trình bằng:
./main
