.. _ROS2Tindakan:

Memahami tindakan
=====================

**Sasaran:** Mengintrospeksi tindakan di ROS 2.

**Tingkat tutorial:** Pemula

**Waktu:** 15 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Tindakan adalah salah satu jenis komunikasi di ROS 2 dan ditujukan untuk tugas yang berjalan lama.
Mereka terdiri dari tiga bagian: tujuan, umpan balik, dan hasil.

Tindakan dibangun berdasarkan topik dan layanan.
Fungsinya mirip dengan layanan, kecuali tindakan dapat dibatalkan.
Mereka juga memberikan umpan balik yang stabil, berbeda dengan layanan yang mengembalikan satu tanggapan.

Tindakan menggunakan model klien-server, mirip dengan model penerbit-pelanggan (dijelaskan dalam :doc:`topics tutorial <../Understanding-ROS2-Topics/Understanding-ROS2-Topics>`).
Node "klien tindakan" mengirimkan tujuan ke node "server tindakan" yang mengakui tujuan tersebut dan mengembalikan aliran umpan balik dan hasilnya.

.. image:: images/Action-SingleActionClient.gif

Prasyarat
-------------

Tutorial ini membangun konsep, seperti :doc:`nodes <../Understanding-ROS2-Nodes/Understanding-ROS2-Nodes>` dan :doc:`topics <../Understanding-ROS2-Topics/Understanding-ROS2-Topics >`, tercakup dalam tutorial sebelumnya.

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


2 Gunakan tindakan
^^^^^^^^^^^^^^^

Saat Anda meluncurkan node ``/teleop_turtle``, Anda akan melihat pesan berikut di terminal Anda:

.. blok kode :: konsol

     Gunakan tombol panah untuk memindahkan kura-kura.
     Gunakan tombol G|B|V|C|D|E|R|T untuk memutar ke orientasi absolut. 'F' untuk membatalkan rotasi.

Mari fokus pada baris kedua, yang berhubungan dengan suatu tindakan.
(Instruksi pertama sesuai dengan topik "cmd_vel", yang dibahas sebelumnya di :doc:`topics tutorial <../Understanding-ROS2-Topics/Understanding-ROS2-Topics>`.)

Perhatikan bahwa tombol huruf ``G|B|V|C|D|E|R|T`` membentuk "kotak" di sekitar tombol ``F`` pada keyboard QWERTY AS (jika Anda tidak menggunakan QWERTY keyboard, lihat `tautan ini <https://upload.wikimedia.org/wikipedia/commons/d/da/KB_United_States.svg>`__ untuk mengikuti).
Setiap posisi tombol di sekitar ``F`` sesuai dengan orientasi tersebut di turtlesim.
Misalnya, ``E`` akan memutar orientasi kura-kura ke pojok kiri atas.

Perhatikan terminal tempat node ``/turtlesim`` berjalan.
Setiap kali Anda menekan salah satu tombol ini, Anda mengirimkan tujuan ke server tindakan yang merupakan bagian dari node ``/turtlesim``.
Tujuannya adalah memutar kura-kura untuk menghadap ke arah tertentu.
Sebuah pesan yang menyampaikan hasil dari tujuan harus ditampilkan setelah penyu menyelesaikan putarannya:

.. blok kode :: konsol

     [INFO] [turtlesim]: Tujuan rotasi berhasil diselesaikan

Tombol ``F`` akan membatalkan tujuan di tengah eksekusi.

Coba tekan tombol ``C``, lalu tekan tombol ``F`` sebelum kura-kura dapat menyelesaikan putarannya.
Di terminal tempat node ``/turtlesim`` berjalan, Anda akan melihat pesan:

.. blok kode :: konsol

   [INFO] [turtlesim]: Tujuan rotasi dibatalkan

Tidak hanya sisi klien (input Anda di teleop) dapat menghentikan tujuan, tetapi sisi server (node ``/turtlesim``) juga bisa.
Ketika sisi server memilih untuk berhenti memproses tujuan, dikatakan "membatalkan" tujuan tersebut.

Coba tekan tombol ``D``, lalu tombol ``G`` sebelum putaran pertama selesai.
Di terminal tempat node ``/turtlesim`` berjalan, Anda akan melihat pesan:

.. blok kode :: konsol

   [WARN] [turtlesim]: Gol rotasi diterima sebelum gol sebelumnya selesai. Membatalkan tujuan sebelumnya

Server aksi ini memilih untuk membatalkan gol pertama karena mendapat gol baru.
Itu bisa memilih sesuatu yang lain, seperti menolak tujuan baru atau mengeksekusi tujuan kedua setelah yang pertama selesai.
Jangan menganggap setiap server tindakan akan memilih untuk membatalkan tujuan saat ini saat mendapatkan yang baru.

3 info simpul ros2
^^^^^^^^^^^^^^^^^^^^

Untuk melihat daftar tindakan yang disediakan node, ``/turtlesim`` dalam hal ini, buka terminal baru dan jalankan perintah:

.. blok kode :: konsol

     info simpul ros2 /turtlesim

Yang akan menampilkan daftar pelanggan, penerbit, layanan, server tindakan, dan klien tindakan ``/turtlesim``:

.. blok kode :: konsol

   /turtlesim
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
       / reset: s