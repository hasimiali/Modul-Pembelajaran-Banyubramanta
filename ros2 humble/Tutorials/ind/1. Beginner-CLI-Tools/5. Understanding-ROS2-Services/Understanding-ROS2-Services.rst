.. _ROS2Layanan:

Memahami layanan
======================

**Sasaran:** Pelajari tentang layanan di ROS 2 menggunakan alat baris perintah.

**Tingkat tutorial:** Pemula

**Waktu:** 10 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Layanan adalah metode komunikasi lain untuk node dalam grafik ROS.
Layanan didasarkan pada model panggilan dan tanggapan versus model topik penerbit-pelanggan.
Sementara topik memungkinkan node untuk berlangganan aliran data dan mendapatkan pembaruan terus-menerus, layanan hanya menyediakan data saat dipanggil secara khusus oleh klien.

.. image:: images/Layanan-SingleServiceClient.gif

.. image:: images/Service-MultipleServiceClient.gif

Prasyarat
-------------

Beberapa konsep yang disebutkan dalam tutorial ini, seperti :doc:`Nodes <../Understanding-ROS2-Nodes/Understanding-ROS2-Nodes>` dan :doc:`Topics <../Understanding-ROS2-Topics/Understanding-ROS2- Topik>`, dibahas dalam tutorial sebelumnya dalam seri ini.

Anda memerlukan :doc:`paket turtlesim <../Introducing-Turtlesim/Introducing-Turtlesim>`.

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

2 daftar layanan ros2
^^^^^^^^^^^^^^^^^^^^^^^

Menjalankan perintah ``ros2 service list`` di terminal baru akan mengembalikan daftar semua layanan yang saat ini aktif di sistem:

.. blok kode :: konsol

   /jernih
   /membunuh
   /mengatur ulang
   /muncul
   /teleop_turtle/describe_parameters
   /teleop_turtle/get_parameter_types
   /teleop_turtle/get_parameters
   /teleop_turtle/list_parameters
   /teleop_turtle/set_parameters
   /teleop_turtle/set_parameters_atomically
   /turtle1/set_pen
   /turtle1/teleport_absolute
   /turtle1/teleport_relative
   /turtlesim/describe_parameters
   /turtlesim/get_parameter_types
   /turtlesim/get_parameters
   /turtlesim/list_parameters
   /turtlesim/set_parameters
   /turtlesim/set_parameters_atomically

Anda akan melihat bahwa kedua node memiliki enam layanan yang sama dengan ``parameter`` di namanya.
Hampir setiap node di ROS 2 memiliki layanan infrastruktur yang dibangun dari parameter ini.
Akan ada lebih banyak tentang parameter di tutorial berikutnya.
Dalam tutorial ini, layanan parameter akan dihilangkan dari diskusi.

Untuk saat ini, mari fokus pada layanan khusus turtlesim, ``/clear``, ``/kill``, ``/reset``, ``/spawn``, ``/turtle1/set_pen``, ` `/turtle1/teleport_absolute``, dan ``/turtle1/teleport_relative``.
Anda mungkin ingat berinteraksi dengan beberapa layanan ini menggunakan rqt di tutorial :doc:`Use turtlesim, ros2, and rqt <../Introducing-Turtlesim/Introducing-Turtlesim>`.


Jenis layanan 3 ros2
^^^^^^^^^^^^^^^^^^^^^^^

Layanan memiliki tipe yang menjelaskan bagaimana data permintaan dan respons dari suatu layanan disusun.
Jenis layanan didefinisikan serupa dengan jenis topik, kecuali jenis layanan memiliki dua bagian: satu pesan untuk permintaan dan satu lagi untuk respons.

Untuk mengetahui jenis layanan, gunakan perintah:

.. blok kode :: konsol

   ros2 jenis layanan <service_name>

Mari kita lihat layanan ``/clear`` turtlesim.
Di terminal baru, masukkan perintah:

.. blok kode :: konsol

   jenis layanan ros2 / jelas

Yang harus dikembalikan:

.. blok kode :: konsol

   std_srvs/srv/Kosong

Tipe ``Empty`` berarti panggilan layanan tidak mengirimkan data saat mengajukan permintaan dan tidak menerima data saat menerima respons.

3.1 daftar layanan ros2 -t
~~~~~~~~~~~~~~~~~~~~~~~~~~

Untuk melihat jenis semua layanan aktif pada saat yang sama, Anda dapat menambahkan opsi ``--show-types``, disingkat ``-t``, ke perintah ``list``:

.. blok kode :: konsol

   daftar layanan ros2 -t

Yang akan mengembalikan:

.. blok kode :: konsol

   /hapus [std_srvs/srv/Kosong]
   /bunuh [turtlesim/srv/Bunuh]
   /reset [std_srvs/srv/Kosong]
   / menelurkan [turtlesim/srv/Menelurkan]
   ...
   /turtle1/set_pen [turtlesim/srv/SetPen]
   /turtle1/teleport_absolute [turtlesim/srv/TeleportAbsolute]
   /turtle1/teleport_relative [turtlesim/srv/TeleportRelative]
   ...

4 layanan ros2 temukan
^^^^^^^^^^^^^^^^^^^^^^^

Jika Anda ingin menemukan semua layanan dari jenis tertentu, Anda dapat menggunakan perintah:

.. blok kode :: konsol

   layanan ros2 temukan <type_name>

Misalnya, Anda dapat menemukan semua layanan yang diketik ``Empty`` seperti ini:

.. blok kode :: konsol

   layanan ros2 temukan std_srvs/srv/Empty

Yang akan mengembalikan:

.. blok kode :: konsol

   /jernih
   /mengatur ulang

Tampilan antarmuka 5 ros2
^^^^^^^^^^^^^^^^^^^^^^^^^^

Anda dapat memanggil layanan dari baris perintah, tetapi pertama-tama Anda perlu mengetahui struktur argumen masukan.

.. blok kode :: konsol

   antarmuka ros2 menampilkan <type_name>

Coba ini pada jenis layanan ``/clear``, ``Empty``:

.. blok kode :: konsol

   antarmuka ros2 menunjukkan std_srvs/srv/Empty

Yang akan mengembalikan:

.. blok kode :: konsol

   ---

``---`` memisahkan