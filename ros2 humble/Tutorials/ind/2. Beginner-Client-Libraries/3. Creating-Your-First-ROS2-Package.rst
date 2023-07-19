.. _Colcon:

Menggunakan ``colcon`` untuk membuat paket
==================================

.. isi :: Daftar Isi
    :kedalaman: 2
    :lokal:

**Sasaran:** Bangun ruang kerja ROS 2 dengan ``colcon``.

**Tingkat tutorial:** Pemula

**Waktu:** 20 menit

Ini adalah tutorial singkat tentang cara membuat dan membangun ruang kerja ROS 2 dengan ``colcon``.
Ini adalah tutorial praktis dan tidak dirancang untuk menggantikan dokumentasi inti.

Latar belakang
----------

``colcon`` adalah iterasi pada alat build ROS ``catkin_make``, ``catkin_make_isolated``, ``catkin_tools`` dan ``ament_tools``.
Untuk informasi lebih lanjut tentang desain colcon, lihat `dokumen ini <https://design.ros2.org/articles/build_tool.html>`__.

Kode sumber dapat ditemukan di organisasi `colcon GitHub <https://github.com/colcon>`__.

Prasyarat
-------------

Instal colcon
^^^^^^^^^^^^^^^^

.. blok kode :: bash

     sudo apt install python3-colcon-common-extensions



Instal ROS2
^^^^^^^^^^^^^^^

Untuk membuat sampel, Anda perlu menginstal ROS 2.

Ikuti :doc:`instruksi instalasi <../../Installation>`.

.. perhatian:: Jika menginstal dari paket Debian, tutorial ini memerlukan :ref:`instalasi desktop <linux-install-debians-install-ros-2-packages>`.

Dasar
------

Ruang kerja ROS adalah direktori dengan struktur tertentu.
Biasanya ada subdirektori ``src``.
Di dalam subdirektori itu adalah tempat kode sumber paket ROS akan ditempatkan.
Biasanya direktori mulai kosong.

colcon melakukan build di luar sumber.
Secara default ini akan membuat direktori berikut sebagai peer dari direktori ``src``:

* Direktori ``build`` akan menjadi tempat file perantara disimpan.
   Untuk setiap paket, subfolder akan dibuat di mana mis. CMake sedang dipanggil.
* Direktori ``install`` adalah tempat setiap paket akan diinstal.
   Secara default setiap paket akan diinstal ke dalam subdirektori yang terpisah.
* Direktori ``log`` berisi berbagai informasi logging tentang setiap pemanggilan colcon.

.. catatan:: Dibandingkan dengan catkin tidak ada direktori ``devel``.

Buat ruang kerja
^^^^^^^^^^^^^^^^^^^^^^

Pertama, buat direktori (``ros2_ws``) untuk memuat ruang kerja kita:

.. blok kode :: bash

     mkdir -p ~/ros2_ws/src
     cd ~/ros2_ws


Pada titik ini ruang kerja berisi satu direktori kosong ``src``:

.. blok kode :: bash

     .
     └── src

     1 direktori, 0 file

Tambahkan beberapa sumber
^^^^^^^^^^^^^^^^^^^^

Mari klon repositori `contoh <https://github.com/ros2/examples>`__ ke dalam direktori ``src`` ruang kerja:

.. blok kode :: bash

     git clone https://github.com/ros2/contoh src/contoh -b {REPOS_FILE_BRANCH}

Sekarang ruang kerja harus memiliki kode sumber ke contoh ROS 2:

.. blok kode :: bash

     .
     └── src
         └── contoh
             ├── KONTRIBUSI.md
             ├── LISENSI
             ├── rclcpp
             ├── rclpy
             └── README.md

     4 direktori, 3 file

Sumber lapisan bawah
^^^^^^^^^^^^^^^^^^^^^^

Penting bagi kita untuk memiliki sumber lingkungan untuk instalasi ROS 2 yang ada yang akan menyediakan ruang kerja kita dengan dependensi build yang diperlukan untuk paket contoh.
Hal ini dicapai dengan mengambil skrip penyiapan yang disediakan oleh instalasi biner atau instalasi sumber, yaitu. ruang kerja colcon lain (lihat :doc:`Instalasi <../../Instalasi>`).
Kami menyebut lingkungan ini sebagai **lapisan bawah**.

Ruang kerja kita, ``ros2_ws``, akan menjadi **overlay** di atas instalasi ROS 2 yang sudah ada.
Secara umum, disarankan untuk menggunakan overlay saat Anda berencana untuk melakukan iterasi pada sejumlah kecil paket, daripada meletakkan semua paket Anda di ruang kerja yang sama.

Bangun ruang kerja
^^^^^^^^^^^^^^^^^^^^^^^

.. Perhatian::

    Untuk membangun paket di Windows, Anda harus berada di lingkungan Visual Studio, lihat :ref:`Membuat Kode ROS 2 <windows-dev-build-ros2>` untuk detail lebih lanjut.

Di root ruang kerja, jalankan ``colcon build``.
Karena tipe build seperti ``ament_cmake`` tidak mendukung konsep ruang ``devel`` dan memerlukan paket untuk diinstal, colcon mendukung opsi ``--symlink-install``.
Ini memungkinkan file yang diinstal diubah dengan mengubah file di ruang ``sumber`` (mis. File Python atau sumber daya lain yang tidak dikompilasi) untuk iterasi yang lebih cepat.

.. blok kode :: konsol

   colcon build --symlink-install


Setelah build selesai, kita akan melihat direktori ``build``, ``install``, dan ``log``:

.. blok kode :: bash

     .
     ├── bangun
     ├── pasang
     ├── mencatat
     └── src

     4 direktori, 0 file

.. _colcon-run-the-tests:

Jalankan tes
^^^^^^^^^

Untuk menjalankan tes untuk paket yang baru saja kita buat, jalankan perintah berikut:

.. blok kode :: konsol

   uji colkon

.. _colcon-tutorial-sumber-lingkungan:

Sumber lingkungan
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ketika colcon berhasil menyelesaikan pembangunan, hasilnya akan berada di direktori ``install``.
Sebelum Anda dapat menggunakan salah satu executable atau pustaka yang diinstal, Anda perlu menambahkannya ke jalur dan jalur pustaka Anda.
colcon akan memiliki