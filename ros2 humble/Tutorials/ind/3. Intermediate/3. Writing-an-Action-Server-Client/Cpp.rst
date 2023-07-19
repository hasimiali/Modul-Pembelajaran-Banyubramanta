.. _ActionsCpp:

Menulis server tindakan dan klien (C++)
=====================================

**Sasaran:** Mengimplementasikan server tindakan dan klien di C++.

**Tingkat tutorial:** Menengah

**Waktu:** 15 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Tindakan adalah bentuk komunikasi asinkron di ROS.
*Klien tindakan* mengirim permintaan sasaran ke *server tindakan*.
*Server tindakan* mengirimkan umpan balik tujuan dan hasil ke *klien tindakan*.

Prasyarat
-------------

Anda memerlukan paket ``custom_action_interfaces`` dan ``Fibonacci.action``
antarmuka yang ditentukan dalam tutorial sebelumnya, :doc:`../Creating-an-Action`.

Tugas
-----

1 Membuat paket custom_action_cpp
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Seperti yang kita lihat di tutorial :doc:`../../Beginner-Client-Libraries/Creating-Your-First-ROS2-Package`, kita perlu membuat paket baru untuk menyimpan C++ dan kode pendukung kita.

1.1 Membuat paket custom_action_cpp
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pergilah ke ruang kerja tindakan yang Anda buat di :doc:`tutorial sebelumnya <../Creating-an-Action>` (ingat untuk sumber ruang kerja), dan buat paket baru untuk server tindakan C++:


.. tab::

   .. grup-tab :: Linux

     .. blok kode :: bash

       cd ~/ros2_ws/src
       ros2 pkg buat --dependencies custom_action_interfaces rclcpp rclcpp_action rclcpp_components --lisensi Apache-2.0 -- custom_action_cpp

   .. grup-tab :: macOS

     .. blok kode :: bash

       cd ~/ros2_ws/src
       ros2 pkg buat --dependencies custom_action_interfaces rclcpp rclcpp_action rclcpp_components --lisensi Apache-2.0 -- custom_action_cpp

   .. grup-tab :: Windows

     .. blok kode :: bash

       cd\ros2_ws\src
       ros2 pkg buat --dependencies custom_action_interfaces rclcpp rclcpp_action rclcpp_components --lisensi Apache-2.0 -- custom_action_cpp

1.2 Menambahkan kontrol visibilitas
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Untuk membuat paket terkompilasi dan bekerja di Windows, kita perlu menambahkan beberapa "kontrol visibilitas".
Untuk detail selengkapnya, lihat :ref:`Visibilitas Simbol Windows di dokumen Tip dan Trik Windows <Windows_Symbol_Visibility>`.

Buka ``custom_action_cpp/include/custom_action_cpp/visibility_control.h``, dan masukkan kode berikut di:

.. blok kode :: c++

   #ifndef CUSTOM_ACTION_CPP__VISIBILITY_CONTROL_H_
   #define CUSTOM_ACTION_CPP__VISIBILITY_CONTROL_H_

   #ifdef __cplusplus
   eksternal "C"
   {
   #berakhir jika

   // Logika ini dipinjam (kemudian diberi spasi nama) dari contoh di wiki gcc:
   // https://gcc.gnu.org/wiki/Visibilitas

   #jika ditentukan _WIN32 || didefinisikan __CYGWIN__
     #ifdef __GNUC__
       #define CUSTOM_ACTION_CPP_EXPORT __attribute__ ((dllexport))
       #define CUSTOM_ACTION_CPP_IMPORT __attribute__ ((dllimport))
     #kalau tidak
       #define CUSTOM_ACTION_CPP_EXPORT __declspec(dllexport)
       #define CUSTOM_ACTION_CPP_IMPORT __declspec(dllimport)
     #berakhir jika
     #ifdef CUSTOM_ACTION_CPP_BUILDING_DLL
       #define CUSTOM_ACTION_CPP_PUBLIC CUSTOM_ACTION_CPP_EXPORT
     #kalau tidak
       #define CUSTOM_ACTION_CPP_PUBLIC CUSTOM_ACTION_CPP_IMPORT
     #berakhir jika
     #menentukan CUSTOM_ACTION_CPP_PUBLIC_TYPE CUSTOM_ACTION_CPP_PUBLIC
     #menentukan CUSTOM_ACTION_CPP_LOCAL
   #kalau tidak
     #define CUSTOM_ACTION_CPP_EXPORT __atribut__ ((visibilitas("default")))
     #menentukan CUSTOM_ACTION_CPP_IMPORT
     #jika __GNUC__ >= 4
       #define CUSTOM_ACTION_CPP_PUBLIC __atribut__ ((visibilitas("default")))
       #define CUSTOM_ACTION_CPP_LOCAL __atribut__ ((visibilitas("tersembunyi")))
     #kalau tidak
       #menentukan CUSTOM_ACTION_CPP_PUBLIC
       #menentukan CUSTOM_ACTION_CPP_LOCAL
     #berakhir jika
     #menentukan CUSTOM_ACTION_CPP_PUBLIC_TYPE
   #berakhir jika

   #ifdef __cplusplus
   }
   #berakhir jika

   #endif // CUSTOM_ACTION_CPP__VISIBILITY_CONTROL_H_

2 Menulis server tindakan
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Mari fokus pada penulisan server aksi yang menghitung deret Fibonacci menggunakan aksi yang kita buat di tutorial :doc:`../Creating-an-Action`.

2.1 Menulis kode server tindakan
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Buka ``custom_action_cpp/src/fibonacci_action_server.cpp``, dan masukkan kode berikut di:

.. literalinclude:: scripts/server.cpp
     :bahasa: c++

Beberapa baris pertama menyertakan semua header yang perlu kita kompilasi.

Selanjutnya kita membuat kelas yang merupakan kelas turunan dari ``rclcpp::Node``:

.. literalinclude:: scripts/server.cpp
     :bahasa: c++
     :baris: 14

Konstruktor untuk kelas ``FibonacciActionServer`` menginisialisasi nama node sebagai ``fibonacci_action_server``:

.. literalinclude:: scripts/server.cpp
     :bahasa: c++
     :baris: 21-22

Konstruktor juga memberi contoh server tindakan baru:

.. literalinclude:: scripts/server.cpp
     :bahasa: c++
     :baris: 26-31

Server tindakan memerlukan 6 hal:

1. Nama jenis tindakan dengan template: ``Fibonacci``.
2. Node ROS 2 untuk menambahkan tindakan ke: ``this``.
3. Nama tindakan: ``'fibonacci'``.
4. Fungsi callback untuk menangani tujuan: ``handle_goal``
5. Fungsi callback untuk menangani pembatalan: ``handle_ca