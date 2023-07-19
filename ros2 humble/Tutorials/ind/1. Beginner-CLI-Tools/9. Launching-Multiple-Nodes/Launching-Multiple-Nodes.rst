.. _ROS2Luncurkan:

Meluncurkan node
===============

**Sasaran:** Gunakan alat baris perintah untuk meluncurkan beberapa node sekaligus.

**Level Tutorial:** Pemula

**Waktu:** 5 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Di sebagian besar tutorial pengantar, Anda telah membuka terminal baru untuk setiap node baru yang Anda jalankan.
Saat Anda membuat sistem yang lebih kompleks dengan semakin banyak node yang berjalan secara bersamaan, membuka terminal dan memasukkan kembali detail konfigurasi menjadi membosankan.

Luncurkan file memungkinkan Anda untuk memulai dan mengonfigurasi sejumlah executable yang berisi node ROS 2 secara bersamaan.

Menjalankan satu file peluncuran dengan perintah ``ros2 launch`` akan memulai seluruh sistem Anda - semua node dan konfigurasinya - sekaligus.

Prasyarat
-------------

Sebelum memulai tutorial ini, instal ROS 2 dengan mengikuti petunjuk pada halaman ROS 2 :doc:`../../../Installation/`.

Perintah yang digunakan dalam tutorial ini menganggap Anda mengikuti panduan instalasi paket biner untuk sistem operasi Anda (paket Debian untuk Linux).
Anda masih dapat mengikuti jika Anda membuat dari sumber, tetapi jalur ke file penyiapan Anda kemungkinan akan berbeda.
Anda juga tidak akan dapat menggunakan perintah ``sudo apt install ros-<distro>-<package>`` (sering digunakan dalam tutorial tingkat pemula) jika Anda menginstal dari sumber.

Jika Anda menggunakan Linux dan belum terbiasa dengan shell, `tutorial ini <http://www.ee.surrey.ac.uk/Teaching/Unix/>`__ akan membantu.

Tugas
-----

Menjalankan File Peluncuran
^^^^^^^^^^^^^^^^^^^^^^^^^^

Buka terminal baru dan jalankan:

.. blok kode :: konsol

    ros2 luncurkan turtlesim multisim.launch.py

Perintah ini akan menjalankan file peluncuran berikut:

.. blok kode :: python

    # turtlesim/launch/multisim.launch.py

    dari peluncuran impor LaunchDescription
    impor launch_ros.actions

    def generate_launch_description():
        kembali LaunchDescription([
            launch_ros.actions.Node(
                namespace= "turtlesim1", package='turtlesim', executable='turtlesim_node', output='screen'),
            launch_ros.actions.Node(
                namespace = "turtlesim2", package='turtlesim', executable='turtlesim_node', output='screen'),
        ])

.. catatan::

   File peluncuran di atas ditulis dengan Python, tetapi Anda juga dapat menggunakan XML dan YAML untuk membuat file peluncuran.
   Anda dapat melihat perbandingan berbagai format peluncuran ROS 2 ini di :doc:`../../../How-To-Guides/Launch-file-different-formats`.

Ini akan menjalankan dua simpul turtlesim:

.. gambar:: gambar/turtlesim_multisim.png

Untuk saat ini, jangan khawatir tentang isi file peluncuran ini.
Anda dapat menemukan informasi selengkapnya tentang peluncuran ROS 2 di :doc:`tutorial peluncuran ROS 2 <../../Intermediate/Launch/Launch-Main>`.

(Opsional) Kontrol Node Turtlesim
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sekarang setelah node ini berjalan, Anda dapat mengontrolnya seperti node ROS 2 lainnya.
Misalnya, Anda dapat membuat kura-kura berjalan berlawanan arah dengan membuka dua terminal tambahan dan menjalankan perintah berikut:

Di terminal kedua:

.. blok kode :: konsol

    pub topik ros2 /turtlesim1/turtle1/cmd_vel geometri_msgs/msg/Twist "{linier: {x: 2.0, y: 0.0, z: 0.0}, sudut: {x: 0.0, y: 0.0, z: 1.8}}"

Di terminal ketiga:

.. blok kode :: konsol

    pub topik ros2 /turtlesim2/turtle1/cmd_vel geometri_msgs/msg/Twist "{linier: {x: 2.0, y: 0.0, z: 0.0}, sudut: {x: 0.0, y: 0.0, z: -1.8}}"

Setelah menjalankan perintah ini, Anda akan melihat sesuatu seperti berikut:

.. gambar:: gambar/turtlesim_multisim_spin.png

Ringkasan
-------

Arti penting dari apa yang telah Anda lakukan sejauh ini adalah Anda telah menjalankan dua node turtlesim dengan satu perintah.
Setelah Anda belajar menulis file peluncuran Anda sendiri, Anda akan dapat menjalankan banyak node - dan mengatur konfigurasinya - dengan cara yang sama, dengan perintah ``ros2 launch``.

Untuk tutorial lebih lanjut tentang file peluncuran ROS 2, lihat :doc:`halaman tutorial file peluncuran utama<../../Intermediate/Launch/Launch-Main>`.

Langkah selanjutnya
----------

Dalam tutorial berikutnya, :doc:`../Recording-And-Playing-Back-Data/Recording-And-Playing-Back-Data`, Anda akan belajar tentang alat bermanfaat lainnya, ``ros2 bag``.