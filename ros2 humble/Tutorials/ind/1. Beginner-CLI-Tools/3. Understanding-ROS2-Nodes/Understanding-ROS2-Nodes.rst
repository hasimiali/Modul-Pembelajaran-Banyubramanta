.. _ROS2Node:

Memahami node
===================

**Sasaran:** Pelajari tentang fungsi node di ROS 2, dan alat untuk berinteraksi dengannya.

**Tingkat tutorial:** Pemula

**Waktu:** 10 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

1 Grafik ROS 2
^^^^^^^^^^^^^^^^^^^^

Selama beberapa tutorial berikutnya, Anda akan belajar tentang serangkaian konsep inti ROS 2 yang membentuk apa yang disebut sebagai "grafik ROS (2)".

Grafik ROS adalah jaringan elemen ROS 2 yang memproses data secara bersamaan pada waktu yang bersamaan.
Ini mencakup semua yang dapat dieksekusi dan koneksi di antara mereka jika Anda memetakan semuanya dan memvisualisasikannya.

2 Node di ROS 2
^^^^^^^^^^^^^^^^^^^^

Setiap node di ROS harus bertanggung jawab untuk satu tujuan modular, mis. mengendalikan motor roda atau menerbitkan data sensor dari pencari jangkauan laser.
Setiap node dapat mengirim dan menerima data dari node lain melalui topik, layanan, tindakan, atau parameter.

.. image:: images/Nodes-TopicandService.gif

Sistem robot penuh terdiri dari banyak node yang bekerja bersama.
Di ROS 2, satu executable (program C++, program Python, dll.) Dapat berisi satu atau lebih node.

Prasyarat
-------------

:doc:`tutorial sebelumnya <../Introducing-Turtlesim/Introducing-Turtlesim>` menunjukkan cara menginstal paket ``turtlesim`` yang digunakan di sini.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../Configuring-ROS2-Environment>`.

Tugas
-----

1 ros2 lari
^^^^^^^^^^

Perintah ``ros2 run`` meluncurkan sebuah executable dari sebuah paket.

.. blok kode :: konsol

     ros2 jalankan <package_name> <executable_name>

Untuk menjalankan turtlesim, buka terminal baru, dan masukkan perintah berikut:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtlesim_node

Jendela turtlesim akan terbuka, seperti yang Anda lihat di :doc:`tutorial sebelumnya <../Introducing-Turtlesim/Introducing-Turtlesim>`.

Di sini, nama paketnya adalah ``turtlesim`` dan nama yang dapat dieksekusi adalah ``turtlesim_node``.

Namun, kami masih belum tahu nama simpulnya.
Anda dapat menemukan nama node dengan menggunakan ``ros2 node list``

2 daftar simpul ros2
^^^^^^^^^^^^^^^^^^^^

``ros2 node list`` akan menampilkan nama semua node yang sedang berjalan.
Ini sangat berguna ketika Anda ingin berinteraksi dengan sebuah node, atau ketika Anda memiliki sistem yang menjalankan banyak node dan perlu melacaknya.

Buka terminal baru saat turtlesim masih berjalan di terminal lain, dan masukkan perintah berikut:

.. blok kode :: konsol

     daftar simpul ros2

Terminal akan mengembalikan nama node:

.. blok kode :: konsol

   /turtlesim

Buka terminal baru lainnya dan mulai teleop node dengan perintah:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtle_teleop_key

Di sini, kami merujuk ke paket ``turtlesim`` lagi, tetapi kali ini kami menargetkan nama yang dapat dieksekusi ``turtle_teleop_key``.

Kembali ke terminal tempat Anda menjalankan ``ros2 node list`` dan jalankan lagi.
Anda sekarang akan melihat nama dua node aktif:

.. blok kode :: konsol

   /turtlesim
   / teleop_turtle

2.1 Pemetaan Ulang
~~~~~~~~~~~~~

`Memetakan ulang <https://design.ros2.org/articles/ros_command_line_arguments.html#name-remapping-rules>`__ memungkinkan Anda menetapkan ulang properti node default, seperti nama node, nama topik, nama layanan, dll., ke kustom nilai-nilai.
Di tutorial terakhir, Anda menggunakan pemetaan ulang pada ``turtle_teleop_key`` untuk mengubah topik cmd_vel dan menargetkan **turtle2**.

Sekarang, mari kita tetapkan kembali nama node ``/turtlesim`` kita.
Di terminal baru, jalankan perintah berikut:

.. blok kode :: konsol

   ros2 jalankan turtlesim turtlesim_node --ros-args --remap __node:=my_turtle

Karena Anda memanggil ``ros2 run`` di turtlesim lagi, jendela turtlesim lain akan terbuka.
Namun, sekarang jika Anda kembali ke terminal tempat Anda menjalankan ``ros2 node list``, dan menjalankannya lagi, Anda akan melihat tiga nama node:

.. blok kode :: konsol

     /my_turtle
     /turtlesim
     / teleop_turtle

3 info simpul ros2
^^^^^^^^^^^^^^^^^^^^

Sekarang setelah Anda mengetahui nama node Anda, Anda dapat mengakses lebih banyak informasi tentangnya dengan:

.. blok kode :: konsol

     info simpul ros2 <node_name>

Untuk memeriksa node terbaru Anda, ``my_turtle``, jalankan perintah berikut:

.. blok kode :: konsol

     info simpul ros2 /my_turtle

``ros2 node info`` menampilkan daftar pelanggan, penerbit, layanan, dan tindakan. yaitu koneksi grafik ROS yang berinteraksi dengan node tersebut.
Outputnya akan terlihat seperti ini:

.. blok kode :: konsol

   /my_turtle
     Pelanggan:
       /parameter_events: rcl_interfaces/msg/ParameterEvent
       /turtle1/cmd_vel: geometri_msgs/msg/Twist
     Penerbit:
       /parameter_events: rcl_interfaces/msg/ParameterEvent
       /rosout: rcl_interfaces/msg/Log
       /turtle1/color_sensor: turtlesim/msg/Color
       /turtle1/pose: turtlesim/msg/Pose
     Server Layanan:
       / hapus: std_srvs/srv/Kosong
       /bunuh: turtlesim/srv/Bunuh
       /my_turtle/describe_parameters: rcl_interfaces/srv/DescribeParameters
       /my_turtle/get_parameter_types: rcl_interfaces/srv/GetParameterTypes
       /my_turtle/get_parameters: rcl_interfaces/srv/GetPara