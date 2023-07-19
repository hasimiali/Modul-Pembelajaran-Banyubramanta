.. _Turtlesim:

Using ``turtlesim``, ``ros2``, and ``rqt``
==========================================

**Goal:** Install and use the turtlesim package and rqt tools to prepare for upcoming tutorials.

**Tutorial level:** Beginner

**Time:** 15 minutes

.. contents:: Contents
   :depth: 2
   :local:

Background
----------

Turtlesim adalah simulator ringan untuk mempelajari ROS 2.
Ini menggambarkan apa yang dilakukan ROS 2 pada tingkat paling dasar untuk memberi Anda gambaran tentang apa yang akan Anda lakukan dengan robot sungguhan atau simulasi robot nanti.

Alat ros2 adalah cara pengguna mengelola, introspeksi, dan berinteraksi dengan sistem ROS.
Ini mendukung banyak perintah yang menargetkan berbagai aspek sistem dan operasinya.
Seseorang mungkin menggunakannya untuk memulai sebuah node, mengatur parameter, mendengarkan topik, dan banyak lagi.
Alat ros2 adalah bagian dari instalasi inti ROS 2.

rqt adalah alat antarmuka pengguna grafis (GUI) untuk ROS 2.
Semua yang dilakukan di rqt dapat dilakukan di baris perintah, tetapi rqt menyediakan cara yang lebih ramah pengguna untuk memanipulasi elemen ROS 2.

Tutorial ini menyentuh konsep inti ROS 2, seperti node, topik, dan layanan.
Semua konsep ini akan diuraikan dalam tutorial selanjutnya; untuk saat ini, Anda cukup menyiapkan alat dan merasakannya.

Prerequisites
-------------

Tutorial sebelumnya, :doc:`../Configuring-ROS2-Environment`, akan menunjukkan cara menyiapkan lingkungan Anda.

Tasks
-----

1 Install turtlesim
^^^^^^^^^^^^^^^^^^^

Seperti biasa, mulailah dengan sumber file setup Anda di terminal baru, seperti yang dijelaskan dalam :doc:`tutorial sebelumnya <../Configuring-ROS2-Environment>`.

Instal paket turtlesim untuk distro ROS 2 Anda:

.. code-block:: console
    sudo apt update

    sudo apt install ros-{DISTRO}-turtlesim

Periksa apakah paket sudah diinstal:

.. code-block:: console

  ros2 pkg executables turtlesim

Perintah di atas harus mengembalikan daftar executable turtlesim:

.. code-block:: console

  turtlesim draw_square
  turtlesim mimic
  turtlesim turtle_teleop_key
  turtlesim turtlesim_node

2 Start turtlesim
^^^^^^^^^^^^^^^^^

Untuk memulai turtlesim, masukkan perintah berikut di terminal Anda:

.. code-block:: console

  ros2 run turtlesim turtlesim_node

Jendela simulator akan muncul, dengan kura-kura acak di tengahnya.

.. image:: images/turtlesim.png

Di terminal, di bawah perintah, Anda akan melihat pesan dari node:

.. code-block:: console

  [INFO] [turtlesim]: Starting turtlesim with node name /turtlesim
  [INFO] [turtlesim]: Spawning turtle [turtle1] at x=[5.544445], y=[5.544445], theta=[0.000000]

Di sana Anda dapat melihat nama kura-kura default dan koordinat tempat ia bertelur.

3 Use turtlesim
^^^^^^^^^^^^^^^

Buka terminal baru dan sumber ROS 2 lagi.

Sekarang Anda akan menjalankan simpul baru untuk mengontrol kura-kura di simpul pertama:

.. code-block:: console

  ros2 run turtlesim turtle_teleop_key

Pada titik ini Anda harus membuka tiga jendela: terminal yang menjalankan ``turtlesim_node``, terminal yang menjalankan ``turtle_teleop_key`` dan jendela turtlesim.
Atur jendela ini sehingga Anda dapat melihat jendela turtlesim, tetapi juga aktifkan terminal ``turtle_teleop_key`` sehingga Anda dapat mengontrol turtle di turtlesim.

Gunakan tombol panah pada keyboard Anda untuk mengontrol kura-kura.
Itu akan bergerak di sekitar layar, menggunakan "pena" yang terpasang untuk menggambar jalur yang diikutinya sejauh ini.

.. note::

  Menekan tombol panah hanya akan menyebabkan penyu bergerak jarak pendek dan kemudian berhenti.
  Ini karena, secara realistis, Anda tidak ingin robot terus menjalankan instruksi jika, misalnya, operator kehilangan koneksi ke robot.

Anda dapat melihat node, dan topik terkait, layanan, dan tindakannya, menggunakan subperintah ``list`` dari masing-masing perintah:

.. code-block:: console

  ros2 node list
  ros2 topic list
  ros2 service list
  ros2 action list

Anda akan belajar lebih banyak tentang konsep-konsep ini dalam tutorial yang akan datang.
Karena tujuan tutorial ini hanya untuk mendapatkan gambaran umum tentang turtlesim, Anda akan menggunakan rqt untuk memanggil beberapa layanan turtlesim dan berinteraksi dengan ``turtlesim_node``.

4 Install rqt
^^^^^^^^^^^^^

Buka terminal baru untuk menginstal ``rqt`` dan pluginnya:

.. code-block:: console

  sudo apt update

  sudo apt install ~nros-{DISTRO}-rqt*

Untuk menjalankan rqt:

.. code-block:: console

  rqt

5 Use rqt
^^^^^^^^^

Saat menjalankan rqt untuk pertama kali, jendela akan kosong.
Jangan khawatir; pilih saja **Plugins** > **Services** > **Service Caller** dari bilah menu di bagian atas.

.. note::

  Mungkin perlu beberapa saat bagi rqt untuk menemukan semua plugin.
  Jika Anda mengklik **Plugins** tetapi tidak melihat **Services** atau opsi lainnya, Anda harus menutup rqt dan memasukkan perintah ``rqt --force-discover`` di terminal Anda.

.. image:: images/rqt.png

Gunakan tombol segarkan di sebelah kiri daftar tarik-turun **Services** untuk memastikan semua layanan simpul turtlesim Anda tersedia.

Klik daftar dropdown **Services** untuk melihat layanan turtlesim, dan pilih layanan ``/spawn``.

5.1 Try the spawn service
~~~~~~~~~~~~~~~~~~~~~~~~~

Mari gunakan rqt untuk memanggil layanan ``/spawn``.
Anda dapat menebak dari namanya bahwa ``/spawn`` akan membuat kura-kura lain di jendela turtlesim.

Beri kura-kura baru nama yang unik, seperti ``turtle2``, dengan mengeklik dua kali di antara tanda kutip tunggal yang kosong di kolom **Expression**.
Anda dapat melihat bahwa ekspresi ini sesuai dengan nilai **name** dan bertipe **string**.

Selanjutnya masukkan beberapa koordinat yang valid untuk menelurkan kura-kura baru, seperti ``x = 1.0`` dan ``y = 1.0``.

.. image:: images/spawn.png

.. note::

  Jika Anda mencoba menelurkan kura-kura baru dengan nama yang sama dengan kura-kura yang ada, seperti ``turtle1`` default, Anda akan mendapatkan pesan kesalahan di terminal yang menjalankan ``turtlesim_node``:

  .. code-block:: console

    [ERROR] [turtlesim]: A turtle named [turtle1] already exists

Untuk menelurkan ``turtle2``, Anda kemudian perlu memanggil layanan dengan mengeklik tombol **Panggil** di sisi kanan atas jendela rqt.

Jika panggilan layanan berhasil, Anda akan melihat kura-kura baru (sekali lagi dengan desain acak) bertelur di koordinat yang Anda masukkan untuk **x** dan **y**.

Jika Anda me-refresh daftar layanan di rqt, Anda juga akan melihat bahwa sekarang ada layanan yang terkait dengan turtle baru, ``/turtle2/...``, selain ``/turtle1/...``.

5.2 Try the set_pen service
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sekarang mari beri ``turtle1`` pena unik menggunakan layanan ``/set_pen``:

.. image:: images/set_pen.png

Nilai untuk **r**, **g** dan **b**, yaitu antara 0 dan 255, menyetel warna pena yang digambar dengan ``turtle1``, dan **width** menyetel ketebalan garis.

Untuk menggambar ``turtle1`` dengan garis merah berbeda, ubah nilai **r** menjadi 255, dan nilai **width** menjadi 5.
Jangan lupa untuk memanggil layanan setelah memperbarui nilainya.

Jika Anda kembali ke terminal tempat ``turtle_teleop_key`` berjalan dan menekan tombol panah, Anda akan melihat pena ``turtle1`` telah berubah.

.. image:: images/new_pen.png

Anda mungkin juga memperhatikan bahwa tidak ada cara untuk memindahkan ``turtle2``.
Itu karena tidak ada teleop node untuk ``turtle2``.

6 Remapping
^^^^^^^^^^^

Anda memerlukan node teleop kedua untuk mengontrol ``turtle2``.
Namun, jika Anda mencoba menjalankan perintah yang sama seperti sebelumnya, Anda akan melihat bahwa perintah ini juga mengontrol ``turtle1``.
Cara untuk mengubah perilaku ini adalah dengan memetakan ulang topik ``cmd_vel``.

Di terminal baru, sumber ROS 2, dan jalankan:

.. code-block:: console

  ros2 run turtlesim turtle_teleop_key --ros-args --remap turtle1/cmd_vel:=turtle2/cmd_vel


Sekarang, Anda dapat memindahkan ``turtle2`` saat terminal ini aktif, dan ``turtle1`` saat terminal lain yang menjalankan ``turtle_teleop_key`` sedang aktif.

.. image:: images/remap.png

7 Close turtlesim
^^^^^^^^^^^^^^^^^

Untuk menghentikan simulasi, Anda dapat memasukkan ``Ctrl + C`` di terminal ``turtlesim_node``, dan ``q`` di terminal ``turtle_teleop_key``.

Summary
-------

Menggunakan turtlesim dan rqt adalah cara yang bagus untuk mempelajari konsep inti ROS 2.

Next steps
----------

Sekarang setelah Anda memiliki turtlesim dan rqt aktif dan berjalan, dan gagasan tentang cara kerjanya, mari selami konsep inti ROS 2 pertama dengan tutorial berikutnya, :doc:`../Understanding-ROS2-Nodes/Understanding-ROS2- Node`.

Related content
---------------

Paket turtlesim dapat ditemukan di `ros_tutorials <https://github.com/ros/ros_tutorials/tree/{REPOS_FILE_BRANCH}/turtlesim>`_ repo.

`Video kontribusi komunitas ini <https://youtu.be/xwT7XWflMdc>`_ menunjukkan banyak item yang tercakup dalam tutorial ini.
