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
| lane_planner | Mengolah data gambar dari kamera bawah menjadi perintah movement yang kemudian dikirim ke comm |
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
   Image.msg (sensor_msgs)
3. Penjelasan:   
   Berdasarkan mission state, perintah dari lane_planner, dan obj_focuss controller mengirimkan perintah berupa movement robot pada comm. Controller juga mempunyai kendali untuk merubah mission state

   | Feedback | Penjelasan  |
   | ----------- | ----------- |
   | 0 | initial |
   | 1 | pindah misi 3 |
   | 2 | pindah misi 4 |

### F.lane_planner
### G.comm
### H.closedloop
### I.aruco_scan
### J.odometry
### K.visual_localisation
### L.source_of_msg
### M.yaml
   
## Cara Labeling dengan Roboflow  
- Membuat akun roboflow terlebih dahulu  
- Roboflow dpat melakukan labeling secara kolaborasi dengan menginvite email anggota  
- Upload dataset yang sudah diambil ke roboflow (Utamakan namanya unik :) agar tidak mudah ditemukan oleh tim lawan), batas upload 10 ribu gambar    
- Membuat project dengan project Bounding Box  
- Menentukan nama dan index dataset terlebih dahulu  
- lakukan labeling dengan mendrag gambar yang akan ditrain  
- Set data train 70%, validation 15%, test 15%  
- Jika ingin mengubah atau menambahkan dapat mengambil data orang terlebih dahulu kemudian dapat menggunakan fitur preprocessing dengan modified class, menggunakan urutan dan menyesuaikan index di txtnya  
- Setelah terlabeli untuk menambah dataset dapat menggunakan augmentasi dan lakukan pengecekan terlebih dahulu terhadap dataset  
- Augmentasi yang pernah dipakai ( Crop: 0% Minimum Zoom, 10% Maximum Zoom   ; Brightness : Between -5% and +5%  ; Blur : Up to 1px)  
- Cek juga terkait kesehatan dataset atau health dataset , yaitu seimbangnya dataset misalkan 1000 usahakan 900an atau 1000an jangan sampai terlalu jauh perbedaannya 

## Instruksi Penyambungan STM32 dengan ROS  
1. Pastikan memiliki aplikasi STM32CubeIDE  
2. Buatlah sebuah workspace jika belum ada
3. Lakukan git clone pada [Link-ini](https://github.com/BanyubramantaITS/STM32_SAUVC2022_F407) dengan cara  
   `git clone https://github.com/BanyubramantaITS/STM32_SAUVC2022_F407.git`  
4. Buka aplikasi STM32CubeIDE  
5. Lakukan debug dengan menekan tombol serangga di toolbar atas
6. Nyalakan live ekspresion
7. Pencet tombol run  
NB: Untuk info lebih lanjut dapat merujuk pada [link ini](https://github.com/BanyubramantaITS/STM32_SAUVC2022_F407)  

## Instruksi Penyambungan Antara Mini PC dengan Laptop  
Atur IP Mini PC dan laptop berdasarkan link video [ini](https://www.youtube.com/watch?v=ck6wtrkdjzs&ab_channel=DemonKiller).   
Jika sudah terkoneksi, sudah dapat dilakukan wake on lan dan remote dekstop.

Penggunaan Wake On Lan:    
a. Download semua file pada link [ini](https://drive.google.com/drive/folders/1PzbhCUMmDWD-AJTcCxMhVdLwtvLPjTpf?usp=sharing)    
b. Buka aplikasi WakeMeOnLan.exe  
c. Lakukan scanning IP dengan tombol play hijau.  
d. Pilih IP yang sesuai dengan yang telah distel sebelumnya.  
e. Klik kanan pada IP tersebut dan klik "Wake Up Selected Computer".
f. Mini PC berhasil dinyalakan apabila terdapat indikator LED biru.  
f. Tunggu selama 15 - 20 detik agar memberikan waktu mini pc untuk booting. 
g. Setelah itu, baru boleh menggunakan remote desktop.  
   
Remote Desktop:  
a. Boot dengan Windows 10 atau Windows 11.  
b. Isikan kolom komputer dengan IP yang telah disetting sebelumnya.  
c. Jika ingin berjalan lebih ringan, ubah settingan di kolom display pada kolom colors menjadi High Color(15 bit).  
d. Klik tombol connect  
e. Masukkan Username dan Password mini pc dengan semuanya huruf kecil.  

Tata Cara Menonaktifkan Mini PC: 
1. Terminate seluruh tab terminal dengan menekan ctrl+c (Sesuai dengan urutan movement->positioning->vision->master->roscore).   
2. Hentikan pengoperasian STM32 dengan menekan tombol terminate (kotak merah).  
3. Exit dari semua aplikasi yang sebelumnya telah dibuka.  
4. Shutdown dengan cara biasanya.   

## Tata Cara Melakukan Perekaman Data Log Pada ROS
1. Pastikan telah menjalankan seluruh command pada semua package diatas
2. Buka tab di terminal baru `rosbag record -a`.  
3. Jika sudah, dapat melakukan `ctrl+c` pada tab record tadi.
4. File tadi akan tersimpan dalam ekstensi `.bag`
5. File ini dapat dimainkan dengan cara `rosbag play [nama file .bag]`
6. Bukan fungsi `rosnode list` dan `rostopic list`.  
   
## Kendala dan Solusi  
1. Kendala:  
   ROS dan YOLOv5 tidak mau mem-publish nilai yang benar ketika digunakan oleh node yang berbeda.  
   Solusi:  
   Gunakan `rospy.Rate(100)` pada file `detect.py` yang semula hanya bernilai 10.  
   
2. Kendala:  
   Pada `Pip install -r requirements.txt` gagal.  
   Solusi:  
   Ulangi lagi proses tersebut dengan koneksi yang lebih stabil.  
   
3. Kendala:  
   Pada Python tidak bisa membaca modul library Serial  
   Solusi:  
   Uninstall library tersebut dan ulangi dengan perintah `sudo python -m pip install pyserial`. ([sumber](https://stackoverflow.com/questions/11403932/python-attributeerror-module-object-has-no-attribute-serial)) 
   
4. Kendala:  
   Library python "Keyboard" harus berjalan ketika sudo. Ketika menjalankan perintah `sudo python3 ....` malah justru rospy tidak terdeteksi. 
   Solusi:  
   Menggunakan python library "getch"  
   
5. Kendala:  
   Repo ini pernah hilang history semua commit-nya.  
   Solusi:  
   Jangan pernah menggunakan `git commit -f` karena akan mereplace history pada repo ini menjadi repo lokal.
   
6. Kendala:    
   Variabel atau message tidak terbaca atau terpublish.    
   Solusi:    
   Memastikan semua message atau variabel disesuaikan urutan dan sudah terpublish maaupun tersubscribe. Untuk kendala nomor 6 dapat dicoba        terlebih dahulu sebelum ke tempat trial untuk efisiensi waktu  
   
7. Kendala:    
   Terdapat delay antara program karena subscribing berkali-kali  
   Solusi:    
   Keluarkan deklarasi subscriber dari while      
   
8. Kendala:  
   Kamera terlalu tinggi exposure-nya.  
   Solusi:  
   Menggunakan ND Filter atau menurunkan dengan obs.  
   
9. Kendala:  
   `Catkin Build` tidak bisa digunakan karena command not found.  
   Solusi:  
   Menjalankan command `sudo apt-get install python3-catkin-tools` untuk menginstall catkin-tools.  
   
## Kendala dan Solusi di Singapura     
1. Kendala:  
   Pembacaan depth sensor mengalami kesalahan ketika 3 digit
   Solusi:
   Mencoba semua kemungkinan yang akan ada. Hal ini dapat terjadi karena selama ini depth hanya bisa membaca 2 digit selama di puker.   
   
2. Kendala:  
   Mengganti nilai variabel ketika di samping kolam pas lomba susah  
   Solusi:  
   Lebih prepare ketika sebelum berangkat ke main stage atau membuat beberapa program dengan variabel yang berbeda. Membuat program open loop
   sebagai cadangan.   
   
3. Kendala:    
   Servo kamera putus sehingga tidak bisa mengambil dataset.      
   Solusi:   
   Mempersiapkan spare sparepart. Akan tetapi, kami tetap dapat mengambil dataset dari panitia selama 1 menit.    

4. Kendala:  
   Minimnya link penyelesaian masalah    
   Solusi:     
   Menambahkan link yang dapat menyelesaikan permasalahan pada readme.     

5. Kendala:    
   Hasil pendeteksian tidak valid karena props dari rulebook berbeda dengan real-life.      
   Solusi:      
   Mengambil dataset baru ketika hari-h(running test).
   
## Rekaman Penurunan Ilmu
1. ROS:    https://drive.google.com/drive/folders/1meryANbCTKu3QCdOLsgfH-7Zj-HfMsAd?usp=sharing
2. Vision: https://drive.google.com/file/d/1rsrxlHd_GfA7oRx8_ec4-OzL_cBGpoL8/view?usp=sharing


##  Kata Mutiara

Jadi pioneer memang tidak mudah, Tapi akan jadi pijakan kuat buat generasi selanjutnya 🏆

By: Sipaling ...
