# Workspace Main Stage ROS SAUVC 2022 Banyubramanta ITS
Repository Banyubramanta ITS untuk Kontes Robot Bawah Air (KRBAI) 2023 dengan implementasi Robot Operating System (ROS).

## Catatan
Dibuat dan dikembangkan menggunakan ROS2 Foxy dari ... 2023 hingga ... 2023 dengan sistem operasi Ubuntu 20.04 LTS. Workspace ini dikembangkan oleh Crew 4,5,dan 6 yang terdiri atas:
1. Azka Bintang Pramudya (3 baris code)
2. Huda
3. Ali
4. Hisan
5. Rizano
6. Bryan

## Daftar Isi  
- [Spesifikasi Robot](#spesifikasi-robot)  
- [Requirements](#requirements)  
- [Daftar Package](#daftar-package-di-dalam-ros)
- [Penjelasan Tiap Package](#penjelasan-tiap-package)  
- [Cara Labeling Dengan Roboflow](#cara-labeling-dengan-roboflow)  
- [Instruksi Penyambungan STM32 dengan ROS](#instruksi-penyambungan-stm32-dengan-ros)     
- [Instruksi Penyambungan Antara Mini PC dengan Laptop](#instruksi-penyambungan-antara-mini-pc-dengan-laptop)  
- [Tata Cara Melakukan Perekaman Data Log Pada ROS](#tata-cara-melakukan-perekaman-data-log-pada-ros)
- [Kendala dan Solusi](#kendala-dan-solusi)    
- [Kendala dan Solusi di Singapura](#kendala-dan-solusi-di-singapura)  
- [Rekaman Penurunan Ilmu](#rekaman-penurunan-ilmu)

  
## Spesifikasi Robot
Robot yang kami develop pada perlombaan ini dinamakan Naru mk II. Berasal dari Bahasa Jawa yang terdiri dari kata "Nara = Raja" dan "mk II = generasi kedua" ketika digabung melebur menjadi "NARUDAKA" artinya raja generasi kedua. Naru mk II memiliki beberapa komponen inti, yaitu:
1. Mini PC: Intel NUC11PAHi7 (Intel Core i7 Gen 11)
2. Mikrokontroller: STM32F407G
3. Kamera 1: Rexus Daxa Trusight 
4. Kamera 2: Rexus Daxa Trusight 
5. Baterai: Li-Po 4 Sel 5000 MAH 2 buah (untuk selain mini pc) & Li-Ion 5 sel 3000 MAH 1 buah (untuk mini pc)  
6. Depth Sensor: MS5837 Blue Robotics  
7. Gyro: GY-25  

## Requirements
1. Sudah terinstall ROS (caranya lihat [disini](https://docs.ros.org/en/foxy/Installation.html)))
2. Menginstall seluruh library yang dibutuhkan oleh Workspace
   
   <!-- `cd src/cv_package/scripts/yolov5`  
   `pip install -r requirements.txt`   -->
   NB: Pastikan koneksi stabil  
3. Menghapus build yang telah ada   
   Pastikan berada di directory `KRBAI_2023_Foxy`    
   Menghapus build yang pernah ada `colcon clean`  
4. Melakukan catkin build  
   `colcon build`  

  
## Daftar Package di Dalam ROS  
[Penjelasan Grafik](https://drive.google.com/file/d/1_YcntQp2rwqfWeKyqn3RxTwLYM25xT1f/view)  

| Nama Package | Fungsi  |
| ----------- | ----------- |
| master | Memberikan output mission state berdasarkan informasi yang diterima |
| yolo | Memberikan output objek yang dilihat dan atributnya |
| bottom_camera | Output gambar dari kamera bawah |
| obj_focuss | Memberikan state pada controller berdasarkan objek yang dilihat dan jarak |
| controller | Memberikan output movement dan state aktuator pada comm |
| lane_planner | Mengolah data gambar dari kamera bawah menjadi perintah movement yang kemudian dikirim ke controller |
| comm | Komunikasi mini pc dan STM |
| closedloop | Robot akan bergerak secara closed loop berdasarkan perintah yang telah ditulis |
| aruco_scan | Mendeteksi aruco tag |
| odometry | Visual odometry berdasarkan perbedan pola pada gambar |
| visual_localisation | Lokalisasi visual berdasarkan pre defined map |
| source_of_msg | Kumpulan custom msg |
| yaml | Kumpulan file yaml |


## Penjelasan Tiap Package
Berikut adalah penjelasan tiap - tiap package yang digunakan (urutan penjalanan program harus sesuai urutan):  

### A.master
1. Deskripsi:   
   Memberikan output mission state berdasarkan informasi yang diterima.
2. Message:   
   Mission.msg  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 state
3. Penjelasan:   
   menerima data hampir dari semua package dan menentukan robot sedang berada pada mission state berapa. Juga mengatur perpindahan mission state.

   | State | Penjelasan  |
   | ----------- | ----------- |
   | 0 | selesai |
   | 1 | jalan 10m |
   | 2 | inspeksi pipa |
   | 3 | menembak torpedo |
   | 4 | masuk docking station |

### B.yolo
1. Deskripsi:   
   Memberikan output objek yang dilihat dan atributnya.
2. Message:   
   Objprop.msg  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;string obj
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 xcent
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 ycent
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 width
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 height
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 dist
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;float64 prob
3. Penjelasan:   
   Mendeteksi objek yang sedang dilihat dan menentukan center point dari objek, serta tinggi dan lebar dalam pixel.

### C.bottom_camera
1. Deskripsi:   
   Output gambar dari kamera bawah.
2. Message:   
   Image.msg (sensor_msgs)
3. Penjelasan:   
   Output gambar dari kamera bawah.

### D.obj_focuss
1. Deskripsi:   
   Memberikan state pada controller berdasarkan objek yang dilihat dan jarak.
2. Message:   
   Objective.msg  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 xcent
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 state
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 ycent
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 scan
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;float64 width
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;float64 height

   Mission.msg (sebagai feedback)
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 state

3. Penjelasan:   
   Memberikan state pada controller berdasarkan objek yang dilihat dan jarak.

   | State | Penjelasan  |
   | ----------- | ----------- |
   | 0 | standby |
   | 1 | bergerak menuju objective yang dikirimkan |
   | 2 | bergerak ke kanan karena objek sudah dekat |
   | 3 | bergerak ke kiri karena objek sudah dekat |
   | 4 | GASPOL |
   | 5 | scanning |
   | 6 | ready tembak torpedo |
   | 7 | siap docking |

   Memberikan feedback pada master.

   | Feedback | Penjelasan  |
   | ----------- | ----------- |
   | 0 | initial |
   | 1 | pindah misi 2 |

### E.controller
1. Deskripsi:   
   Memberikan output movement dan state aktuator pada comm.
2. Message:   
   Controller.msg  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 left_x
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 left_y
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 right_x
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 right_y
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 depth
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 yaw
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 pitch
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 roll
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 py
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 iy
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 dy
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 pp
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 ip
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 dp
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 pr
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 ir
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 dr
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 pd
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 id
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 dd
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 torpedo
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 cal
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 pid_ops
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 dep_ops
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 throttle
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 led_state

   Mission.msg (sebagai feedback)
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 state

3. Penjelasan:   
   Berdasarkan mission state, perintah dari lane_planner, dan obj_focuss controller mengirimkan perintah berupa movement robot pada comm. Controller juga mempunyai kendali untuk merubah mission state

   | Feedback | Penjelasan  |
   | ----------- | ----------- |
   | 0 | initial |
   | 1 | pindah misi 3 |
   | 2 | pindah misi 4 |

### F.lane_planner
1. Deskripsi:   
   Mengolah data gambar dari kamera bawah menjadi perintah movement yang kemudian dikirim ke controller.
2. Message:   
   Lane.msg
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 xcent
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 ycent
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 heading
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 cmd
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 distance
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;int64 angle 

3. Penjelasan:   
   Mengolah data gambar dari kamera bawah menggunakan segmentasi warna dan membagi layar menjadi grid 3x3 dan mengirimkan perintah movement berdasarkan grid mana saja yang bernilai true.

   | cmd | Penjelasan  |
   | ----------- | ----------- |
   | 1 | maju |
   | 2 | centering ke kiri |
   | 3 | centering ke kanan |
   | 4 | maju |
   | 5 | diam |

### G.comm
### H.closedloop
### I.aruco_scan
### J.odometry
### K.visual_localisation
### L.source_of_msg
### M.yaml
   