.. _ROS2Bag:

Merekam dan memutar ulang data
===========================

**Sasaran:** Rekam data yang dipublikasikan tentang suatu topik sehingga Anda dapat memutar ulang dan memeriksanya kapan saja.

**Tingkat tutorial:** Pemula

**Waktu:** 10 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

``ros2 bag`` adalah alat baris perintah untuk merekam data yang diterbitkan pada topik di sistem Anda.
Itu mengakumulasi data yang diteruskan pada sejumlah topik dan menyimpannya dalam database.
Anda kemudian dapat memutar ulang data untuk mereproduksi hasil pengujian dan eksperimen Anda.
Merekam topik juga merupakan cara yang bagus untuk membagikan pekerjaan Anda dan mengizinkan orang lain untuk membuatnya kembali.


Prasyarat
-------------

Anda harus menginstal ``tas ros2`` sebagai bagian dari pengaturan ROS 2 reguler Anda.

Jika Anda menginstal ROS dari paket Debian di Linux dan sistem Anda tidak mengenali perintah tersebut, instal seperti ini:

.. blok kode :: konsol

   sudo apt-get install ros-{DISTRO}-ros2bag \
                        ros-{DISTRO}-rosbag2-storage-default-plugins

Tutorial ini berbicara tentang konsep yang tercakup dalam tutorial sebelumnya, seperti :doc:`nodes <../Understanding-ROS2-Nodes/Understanding-ROS2-Nodes>` dan :doc:`topics <../Understanding-ROS2-Topics/Understanding -ROS2-Topik>`.
Ini juga menggunakan :doc:`turtlesim package <../Introducing-Turtlesim/Introducing-Turtlesim>`.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../Configuring-ROS2-Environment>`.


Tugas
-----

1 Pengaturan
^^^^^^^
Anda akan merekam input keyboard Anda di sistem ``turtlesim`` untuk disimpan dan diputar ulang nanti, jadi mulailah dengan memulai node ``/turtlesim`` dan ``/teleop_turtle``.

Buka terminal baru dan jalankan:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtlesim_node

Buka terminal lain dan jalankan:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtle_teleop_key

Mari kita buat juga direktori baru untuk menyimpan rekaman yang kita simpan, seperti latihan yang baik:

.. blok kode :: konsol

   mkdir bag_files
   cd_bag_files

2 Pilih topik
^^^^^^^^^^^^^^^^^^^^

``ros2 bag`` hanya dapat merekam data dari pesan yang diterbitkan dalam topik.
Untuk melihat daftar topik sistem Anda, buka terminal baru dan jalankan perintah:

.. blok kode :: konsol

   daftar topik ros2

Yang akan mengembalikan:

.. blok kode :: konsol

   /parameter_events
   /rosout
   /turtle1/cmd_vel
   /turtle1/color_sensor
   /turtle1/pose

Dalam tutorial topik, Anda mempelajari bahwa node ``/turtle_teleop`` menerbitkan perintah pada topik ``/turtle1/cmd_vel`` untuk membuat kura-kura bergerak di turtlesim.

Untuk melihat data yang diterbitkan ``/turtle1/cmd_vel``, jalankan perintah:

.. blok kode :: konsol

   ros2 topik gema /turtle1/cmd_vel

Tidak ada yang akan muncul pada awalnya karena tidak ada data yang dipublikasikan oleh teleop.
Kembali ke terminal tempat Anda menjalankan teleop dan pilih agar aktif.
Gunakan tombol panah untuk menggerakkan kura-kura, dan Anda akan melihat data dipublikasikan di terminal yang menjalankan ``ros2 topic echo``.

.. blok kode :: konsol

   linier:
     x: 2.0
     y: 0,0
     z: 0,0
   sudut:
     x: 0,0
     y: 0,0
     z: 0,0
     ---



3 rekor kantong ros2
^^^^^^^^^^^^^^^^^^^^

3.1 Format perekaman
~~~~~~~~~~~~~~~~~~~~~~~

Secara default, ``ros2 bag record`` akan merekam file data menggunakan `format file MCAP <https://mcap.dev>`_ (``.mcap``).

Untuk merekam file menggunakan format file `SQLite3 <https://www.sqlite.org/index.html>`_ (``.db3``), tambahkan flag ``--storage sqlite3`` (atau `` -s sqlite3``) ke perintah ``ros2 bag record`` Anda.

Untuk informasi selengkapnya tentang `ROS 2 storage plugin options <https://github.com/ros2/rosbag2/tree/{DISTRO}/#storage-format-plugin-architecture>`_, lihat referensi berikut:

* `MCAP <https://github.com/ros2/rosbag2/blob/{DISTRO}/rosbag2_storage_mcap/README.md#writer-configuration>`_
* `SQLite3 <https://github.com/ros2/rosbag2/blob/{DISTRO}/rosbag2_storage_sqlite3/README.md#storage-configuration-file>`_


3.2 Rekam satu topik
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Untuk merekam data yang dipublikasikan ke suatu topik, gunakan sintaks perintah:

.. blok kode :: konsol

     catatan tas ros2 <topic_name>

Sebelum menjalankan perintah ini pada topik pilihan Anda, buka terminal baru dan pindah ke direktori ``bag_files`` yang Anda buat sebelumnya, karena file rosbag akan disimpan di direktori tempat Anda menjalankannya.

Jalankan perintah:

.. blok kode :: konsol

     catatan tas ros2 /turtle1/cmd_vel

Anda akan melihat pesan berikut di terminal (tanggal dan waktu akan berbeda):

.. blok kode :: konsol

     [INFO] [rosbag2_storage]: Membuka database 'rosbag2_2019_10_11-05_18_45'.
     [INFO] [rosbag2_transport]: Mendengarkan topik...
     [INFO] [rosbag2_transport]: Berlangganan topik '/turtle1/cmd_vel'
     [INFO] [rosbag2_transport]: Semua topik yang diminta telah dilanggan. Menghentikan penemuan...

Sekarang ``ros2 bag`` merekam data yang diterbitkan pada topik ``/turtle1/cmd_vel``.
Kembali ke terminal teleop dan pindahkan kura-kura lagi.
Gerakannya tidak masalah, tetapi cobalah membuat pola yang dapat dikenali untuk dilihat saat Anda memutar ulang data nanti.

.. gambar:: gambar/rekaman.pn