.. _Turtlesim:

Menggunakan ``turtlesim``, ``ros2``, dan ``rqt``
==========================================

**Tujuan:** Instal dan gunakan paket turtlesim dan alat rqt untuk mempersiapkan tutorial yang akan datang.

**Tingkat tutorial:** Pemula

**Waktu:** 15 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Turtlesim adalah simulator ringan untuk mempelajari ROS 2.
Ini menggambarkan apa yang dilakukan ROS 2 pada level paling dasar untuk memberi Anda gambaran tentang apa yang akan Anda lakukan dengan robot mewarnai atau simulasi robot nanti.

Alat ros2 adalah cara pengguna mengelola, introspeksi, dan berinteraksi dengan sistem ROS.
Ini mendukung banyak perintah yang menargetkan berbagai aspek sistem dan operasinya.
Seseorang mungkin menggunakannya untuk memulai sebuah node, mengatur parameter, mendengarkan topik, dan banyak lagi.
Alat ros2 adalah bagian dari instalasi inti ROS 2.

rqt adalah alat antarmuka pengguna grafis (GUI) untuk ROS 2.
Semua yang dilakukan di rqt dapat dilakukan di baris perintah, tetapi rqt menyediakan cara yang lebih ramah pengguna untuk memanipulasi elemen ROS 2.

Tutorial ini menyentuh konsep inti ROS 2, seperti node, topik, dan layanan.
Semua konsep ini akan diuraikan dalam tutorial selanjutnya; untuk saat ini, Anda cukup menyiapkan alat dan merasakannya.

Prasyarat
-------------

Tutorial sebelumnya, :doc:`../Configuring-ROS2-Environment`, akan menunjukkan cara menyiapkan lingkungan Anda.

Tugas
-----

1 Instal turtlesim
^^^^^^^^^^^^^^^^^^^^^^^

Seperti biasa, mulailah dengan penyiapan sumber file Anda di terminal baru, seperti yang dijelaskan dalam :doc:`tutorial sebelumnya <../Configuring-ROS2-Environment>`.

Instal paket turtlesim untuk distro ROS 2 Anda:

.. blok kode :: konsol
     pembaruan apt sudo

     sudo apt install ros-{DISTRO}-turtlesim

Periksa apakah paket sudah diinstal:

.. blok kode :: konsol

   ros2 pkg dapat dieksekusi turtlesim

Perintah di atas harus mengembalikan daftar executable turtlesim:

.. blok kode :: konsol

   draw_square turtlesim
   tiruan turtlesim
   turtlesim turtle_teleop_key
   turtlesim turtlesim_node

2 Mulai turtlesim
^^^^^^^^^^^^^^^^^^^^

Untuk memulai turtlesim, masukkan perintah berikut di terminal Anda:

.. blok kode :: konsol

   ros2 jalankan turtlesim turtlesim_node

Jendela simulator akan muncul, dengan kura-kura acak di tengahnya.

.. image:: images/turtlesim.png

Di terminal, di bawah perintah, Anda akan melihat pesan dari node:

.. blok kode :: konsol

   [INFO] [turtlesim]: Memulai turtlesim dengan nama node /turtlesim
   [INFO] [turtlesim]: Penyu bertelur [turtle1] di x=[5.544445], y=[5.544445], theta=[0.000000]

Di sana Anda dapat melihat nama kura-kura default dan koordinat tempat ia bertelur.

3 Gunakan turtlesim
^^^^^^^^^^^^^^^^^^

Buka terminal baru dan sumber ROS 2 lagi.

Sekarang Anda akan mengalami akhir baru untuk mengontrol kura-kura di akhir pertama:

.. blok kode :: konsol

   ros2 jalankan turtlesim turtle_teleop_key

Pada titik ini Anda harus membuka tiga jendela: terminal yang menjalankan ``turtlesim_node``, terminal yang menjalankan ``turtle_teleop_key`` dan jendela turtlesim.
Atur jendela ini sehingga Anda dapat melihat jendela turtlesim, tetapi aktifkan juga terminal ``turtle_teleop_key`` sehingga Anda dapat mengontrol turtle di turtlesim.

Gunakan tombol panah pada keyboard Anda untuk mengontrol kura-kura.
Itu akan bergerak di sekitar layar, menggunakan "pena" yang terpasang untuk menggambar jalur yang diikuti sejauh ini.

.. catatan::

   Menekan tombol panah hanya akan menyebabkan penyu bergerak dalam jarak pendek dan kemudian berhenti.
   Ini karena, secara realistis, Anda tidak ingin robot terus menjalankan instruksi jika, misalnya, operator kehilangan koneksi ke robot.

Anda dapat melihat node, dan topik terkait, layanan, dan tindakannya, menggunakan subperintah ``list`` dari masing-masing perintah:

.. blok kode :: konsol

   daftar simpul ros2
   daftar topik ros2
   daftar layanan ros2
   daftar tindakan ros2

Anda akan belajar lebih banyak tentang konsep-konsep ini dalam tutorial yang akan datang.
Karena tujuan tutorial ini hanya untuk mendapatkan gambaran umum tentang turtlesim, Anda akan menggunakan rqt untuk memanggil beberapa layanan turtlesim dan berinteraksi dengan ``turtlesim_node``.

4 Instal rqt
^^^^^^^^^^^^^^^

Buka terminal baru untuk menginstal ``rqt`` dan pluginnya:

.. blok kode :: konsol

   pembaruan apt sudo

   sudo apt install ~nros-{DISTRO}-rqt*

Untuk menjalankan rqt:

.. blok kode :: konsol

   rqt

5 Gunakan rqt
^^^^^^^^^

Saat menjalankan rqt untuk pertama kali, jendela akan kosong.
Jangan khawatir; pilih saja **Plugins** > **Services** > **Service Caller** dari bilah menu di bagian atas.

.. catatan::

   Mungkin perlu beberapa saat bagi rqt untuk menemukan semua plugin.
   Jika Anda mengklik **Plugins** tetapi tidak melihat **Services** atau opsi lainnya, Anda harus menutup rqt dan memasukkan perintah ``rqt --force-discover`` di terminal Anda.

.. gambar:: gambar/rqt.png

Gunakan tombol segarkan di sebelah kiri daftar tarik