.. _ROS2Topik:

Memahami topik
====================

**Sasaran:** Gunakan rqt_graph dan fitur baris perintah untuk mengintrospeksi topik ROS 2.

**Tingkat tutorial:** Pemula

**Waktu:** 20 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

ROS 2 memecah sistem yang kompleks menjadi banyak node modular.
Topik adalah elemen penting dari grafik ROS yang bertindak sebagai bus bagi node untuk bertukar pesan.

.. image:: images/Topic-SinglePublisherandSingleSubscriber.gif

Node dapat menerbitkan data ke sejumlah topik dan secara bersamaan memiliki langganan ke sejumlah topik.

.. image:: images/Topic-MultiplePublisherandMultipleSubscriber.gif

Topik adalah salah satu cara utama di mana data dipindahkan antar node dan oleh karena itu di antara berbagai bagian sistem.


Prasyarat
-------------

:doc:`tutorial sebelumnya <../Understanding-ROS2-Nodes/Understanding-ROS2-Nodes>` memberikan beberapa informasi latar belakang yang berguna tentang node yang dibangun di sini.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../Configuring-ROS2-Environment>`.

Tugas
-----

1 Pengaturan
^^^^^^^

Sekarang Anda seharusnya sudah nyaman memulai turtlesim.

Buka terminal baru dan jalankan:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtlesim_node

Buka terminal lain dan jalankan:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtle_teleop_key

Ingat dari :doc:`tutorial sebelumnya <../Understanding-ROS2-Nodes/Understanding-ROS2-Nodes>` bahwa nama node ini adalah ``/turtlesim`` dan ``/teleop_turtle`` secara default.


2 rqt_graph
^^^^^^^^^^^^

Sepanjang tutorial ini, kita akan menggunakan ``rqt_graph`` untuk memvisualisasikan node dan topik yang berubah, serta hubungan di antara keduanya.

:doc:`turtlesim tutorial <../Introducing-Turtlesim/Introducing-Turtlesim>` memberi tahu Anda cara menginstal rqt dan semua pluginnya, termasuk ``rqt_graph``.

Untuk menjalankan rqt_graph, buka terminal baru dan masukkan perintah:

.. blok kode :: konsol

     rqt_graph

Anda juga dapat membuka rqt_graph dengan membuka ``rqt`` dan memilih **Plugins** > **Introspection** > **Node Graph**.

.. gambar:: gambar/rqt_graph.png

Anda akan melihat node dan topik di atas, serta dua tindakan di sekitar pinggiran grafik (mari kita abaikan untuk saat ini).
Jika Anda mengarahkan mouse ke topik di tengah, Anda akan melihat penyorotan warna seperti pada gambar di atas.

Grafik menggambarkan bagaimana node ``/turtlesim`` dan node ``/teleop_turtle`` berkomunikasi satu sama lain melalui suatu topik.
Node ``/teleop_turtle`` memublikasikan data (penekanan tombol yang Anda masukkan untuk memindahkan kura-kura) ke topik ``/turtle1/cmd_vel``, dan node ``/turtlesim`` berlangganan topik tersebut untuk menerima data.

Fitur penyorotan rqt_graph sangat membantu saat memeriksa sistem yang lebih kompleks dengan banyak node dan topik yang terhubung dengan berbagai cara.

rqt_graph adalah alat introspeksi grafis.
Sekarang kita akan melihat beberapa alat baris perintah untuk introspeksi topik.


3 daftar topik ros2
^^^^^^^^^^^^^^^^^^^^

Menjalankan perintah ``ros2 topic list`` di terminal baru akan menampilkan daftar semua topik yang sedang aktif di sistem:

.. blok kode :: konsol

   /parameter_events
   /rosout
   /turtle1/cmd_vel
   /turtle1/color_sensor
   /turtle1/pose

``ros2 topic list -t`` akan mengembalikan daftar topik yang sama, kali ini dengan jenis topik ditambahkan dalam tanda kurung:

.. blok kode :: konsol

   /parameter_events [rcl_interfaces/msg/ParameterEvent]
   /rosout [rcl_interfaces/msg/Log]
   /turtle1/cmd_vel [geometry_msgs/msg/Twist]
   /turtle1/color_sensor [turtlesim/msg/Warna]
   /turtle1/pose [turtlesim/msg/Pose]

Atribut ini, terutama jenisnya, adalah cara node mengetahui bahwa mereka membicarakan informasi yang sama saat berpindah topik.

Jika Anda bertanya-tanya di mana semua topik ini berada di rqt_graph, Anda dapat menghapus centang semua kotak di bawah **Sembunyikan:**

.. image:: images/unhide.png

Untuk saat ini, biarkan opsi tersebut dicentang untuk menghindari kebingungan.

4 ros2 topik gema
^^^^^^^^^^^^^^^^^^^^

Untuk melihat data yang diterbitkan pada suatu topik, gunakan:

.. blok kode :: konsol

     gema topik ros2 <nama_topik>

Karena kita tahu bahwa ``/teleop_turtle`` memublikasikan data ke ``/turtlesim`` pada topik ``/turtle1/cmd_vel``, mari gunakan ``echo`` untuk mengintrospeksi topik tersebut:

.. blok kode :: konsol

     ros2 topik gema /turtle1/cmd_vel

Pada awalnya, perintah ini tidak akan mengembalikan data apa pun.
Itu karena menunggu ``/teleop_turtle`` untuk menerbitkan sesuatu.

Kembali ke terminal tempat ``turtle_teleop_key`` berjalan dan gunakan tanda panah untuk menggerakkan kura-kura.
Perhatikan terminal tempat ``echo`` Anda berjalan pada saat yang sama, dan Anda akan melihat data posisi dipublikasikan untuk setiap gerakan yang Anda lakukan:

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

Sekarang kembali ke rqt_graph dan hapus centang pada kotak **Debug**.

.. gambar:: gambar/debug.png

``/_ros2cli_26646`` adalah simpul yang dibuat oleh perintah ``echo`` yang baru saja kita jalankan (nomornya mungkin berbeda).
Sekarang kamu bisa