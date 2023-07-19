.. _ROS2Param:

Memahami parameter
========================

**Sasaran:** Pelajari cara mendapatkan, menyetel, menyimpan, dan memuat ulang parameter di ROS 2.

**Tingkat tutorial:** Pemula

**Waktu:** 5 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Parameter adalah nilai konfigurasi dari sebuah node.
Anda dapat menganggap parameter sebagai pengaturan node.
Node dapat menyimpan parameter sebagai bilangan bulat, float, boolean, string, dan daftar.
Di ROS 2, setiap node mempertahankan parameternya sendiri.
Untuk latar belakang lebih lanjut tentang parameter, silakan lihat :doc:`the concept document <../../../Concepts/Basic/About-Parameters>`.

Prasyarat
-------------

Tutorial ini menggunakan :doc:`turtlesim package <../Introducing-Turtlesim/Introducing-Turtlesim>`.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../Configuring-ROS2-Environment>`.

Tugas
-----

1 Pengaturan
^^^^^^^

Mulai dua simpul turtlesim, ``/turtlesim`` dan ``/teleop_turtle``.

Buka terminal baru dan jalankan:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtlesim_node

Buka terminal lain dan jalankan:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtle_teleop_key


2 daftar param ros2
^^^^^^^^^^^^^^^^^^^^

Untuk melihat parameter milik node Anda, buka terminal baru dan masukkan perintah:

.. blok kode :: konsol

     daftar param ros2

Anda akan melihat ruang nama node, ``/teleop_turtle`` dan ``/turtlesim``, diikuti dengan parameter setiap node:

.. blok kode :: konsol

   / teleop_turtle:
     qos_overrides./parameter_events.publisher.depth
     qos_overrides./parameter_events.publisher.durability
     qos_overrides./parameter_events.publisher.history
     qos_overrides./parameter_events.publisher.reliability
     scale_angular
     scale_linear
     gunakan_sim_waktu
   /turtlesim:
     background_b
     background_g
     background_r
     qos_overrides./parameter_events.publisher.depth
     qos_overrides./parameter_events.publisher.durability
     qos_overrides./parameter_events.publisher.history
     qos_overrides./parameter_events.publisher.reliability
     gunakan_sim_waktu

Setiap node memiliki parameter ``use_sim_time``; itu tidak unik untuk turtlesim.

Berdasarkan namanya, sepertinya parameter ``/turtlesim`` menentukan warna latar belakang jendela turtlesim menggunakan nilai warna RGB.

Untuk menentukan jenis parameter, Anda dapat menggunakan ``ros2 param get``.


3 ros2 param dapatkan
^^^^^^^^^^^^^^^^^^^^

Untuk menampilkan tipe dan nilai parameter saat ini, gunakan perintah:

.. blok kode :: konsol

     ros2 param dapatkan <node_name> <parameter_name>

Mari cari tahu nilai parameter ``/turtlesim`` saat ini ``background_g``:

.. blok kode :: konsol

     ros2 param dapatkan /turtlesim background_g

Yang akan mengembalikan nilai:

.. blok kode :: konsol

     Nilai bilangan bulat adalah: 86

Sekarang Anda tahu ``background_g`` memiliki nilai bilangan bulat.

Jika Anda menjalankan perintah yang sama pada ``background_r`` dan ``background_b``, Anda akan mendapatkan nilai masing-masing ``69`` dan ``255``.

4 set parameter ros2
^^^^^^^^^^^^^^^^^^^^

Untuk mengubah nilai parameter saat runtime, gunakan perintah:

.. blok kode :: konsol

     parameter ros2 mengatur <nama_simpul> <nama_parameter> <nilai>

Mari ubah warna latar belakang ``/turtlesim``:

.. blok kode :: konsol

     set param ros2 /turtlesim background_r 150

Terminal Anda harus mengembalikan pesan:

.. blok kode :: konsol

   Setel parameter berhasil

Dan latar belakang jendela turtlesim Anda akan berubah warna:

.. gambar:: gambar/set.png

Mengatur parameter dengan perintah ``set`` hanya akan mengubahnya di sesi Anda saat ini, tidak secara permanen.
Namun, Anda dapat menyimpan pengaturan Anda dan memuatnya kembali saat Anda memulai node berikutnya.

5 ros2 param dump
^^^^^^^^^^^^^^^^^^^^

Anda dapat melihat semua nilai parameter node saat ini dengan menggunakan perintah:

.. blok kode :: konsol

   ros2 param membuang <node_name>

Perintah mencetak ke output standar (stdout) secara default tetapi Anda juga dapat mengarahkan ulang nilai parameter ke dalam file untuk menyimpannya nanti.
Untuk menyimpan konfigurasi parameter ``/turtlesim`` Anda saat ini ke dalam file ``turtlesim.yaml``, masukkan perintah:

.. blok kode :: konsol

   ros2 param dump /turtlesim > turtlesim.yaml

Anda akan menemukan file baru di direktori kerja saat ini di mana shell Anda berjalan.
Jika Anda membuka file ini, Anda akan melihat konten berikut:

.. blok kode :: YAML

   /turtlesim:
     ros__parameter:
       background_b: 255
       background_g: 86
       background_r: 150
       qos_overrides:
         /parameter_events:
           penerbit:
             kedalaman: 1000
             daya tahan: mudah menguap
             riwayat: keep_last
             keandalan: dapat diandalkan
       use_sim_time: salah

Parameter dumping berguna jika Anda ingin memuat ulang node dengan parameter yang sama di masa mendatang.

6 ros2 beban param
^^^^^^^^^^^^^^^^^^^^

Anda dapat memuat parameter dari file ke node yang sedang berjalan menggunakan perintah:

.. blok kode :: konsol

   ros2 param memuat <node_name> <parameter_file>

Untuk memuat file ``turtlesim.yaml`` yang dihasilkan dengan ``ros2 param dump`` ke dalam ``/turtlesim``