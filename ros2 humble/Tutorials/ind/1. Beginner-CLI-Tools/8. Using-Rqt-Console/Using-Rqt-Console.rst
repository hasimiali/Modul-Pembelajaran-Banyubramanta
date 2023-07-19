.. _rqt_console:

Menggunakan ``rqt_console`` untuk melihat log
==================================

**Sasaran:** Mengenal ``rqt_console``, alat untuk mengintrospeksi pesan log.

**Tingkat tutorial:** Pemula

**Waktu:** 5 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

``rqt_console`` adalah alat GUI yang digunakan untuk mengintrospeksi pesan log di ROS 2.
Biasanya, pesan log muncul di terminal Anda.
Dengan ``rqt_console``, Anda dapat mengumpulkan pesan-pesan itu dari waktu ke waktu, melihatnya dengan cermat dan dengan cara yang lebih teratur, memfilternya, menyimpannya, dan bahkan memuat ulang file yang disimpan untuk introspeksi pada waktu yang berbeda.

Node menggunakan log untuk menampilkan pesan tentang peristiwa dan status dalam berbagai cara.
Konten mereka biasanya informatif, demi kepentingan pengguna.

Prasyarat
-------------

Anda perlu menginstal :doc:`rqt_console dan turtlesim <../Introducing-Turtlesim/Introducing-Turtlesim>`.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../Configuring-ROS2-Environment>`.


Tugas
-----

1 Pengaturan
^^^^^^^

Mulai ``rqt_console`` di terminal baru dengan perintah berikut:

.. blok kode :: konsol

     ros2 jalankan rqt_console rqt_console

Jendela ``rqt_console`` akan terbuka:

.. gambar:: gambar/konsol.png

Bagian pertama konsol adalah tempat pesan log dari sistem Anda akan ditampilkan.

Di bagian tengah, Anda memiliki opsi untuk memfilter pesan dengan mengecualikan tingkat keparahan.
Anda juga dapat menambahkan lebih banyak filter pengecualian menggunakan tombol tanda tambah di sebelah kanan.

Bagian bawah adalah untuk menyorot pesan yang menyertakan string yang Anda masukkan.
Anda juga dapat menambahkan lebih banyak filter ke bagian ini.

Sekarang mulai ``turtlesim`` di terminal baru dengan perintah berikut:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtlesim_node

2 Pesan di rqt_console
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Untuk menghasilkan pesan log agar ``rqt_console`` ditampilkan, biarkan kura-kura berlari ke dinding.
Di terminal baru, masukkan perintah ``ros2 topic pub`` (dibahas secara detail di :doc:`topics tutorial <../Understanding-ROS2-Topics/Understanding-ROS2-Topics>`) di bawah:

.. blok kode :: konsol

     ros2 topik pub -r 1 /turtle1/cmd_vel geometri_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 0.0}}"

Karena perintah di atas menerbitkan topik dengan kecepatan tetap, kura-kura terus berlari ke dinding.
Di ``rqt_console`` Anda akan melihat pesan yang sama dengan tingkat keparahan ``Warn`` ditampilkan berulang kali, seperti:

.. gambar:: gambar/peringatan.png

Tekan ``Ctrl+C`` di terminal tempat Anda menjalankan perintah ``ros2 topic pub`` untuk menghentikan kura-kura Anda berlari ke dinding.

3 tingkat penebang
^^^^^^^^^^^^^^^^^^

Level logger ROS 2 diurutkan berdasarkan tingkat keparahan:

.. blok kode :: konsol

     Fatal
     Kesalahan
     Memperingatkan
     Info
     Debug

Tidak ada standar pasti untuk apa yang ditunjukkan setiap level, tetapi aman untuk berasumsi bahwa:

* Pesan ``Fatal`` menunjukkan sistem akan dihentikan untuk mencoba melindungi diri dari kerusakan.
* Pesan ``Error`` menunjukkan masalah signifikan yang tidak serta merta merusak sistem, tetapi mencegahnya berfungsi dengan baik.
* Pesan ``Peringatan`` menunjukkan aktivitas yang tidak terduga atau hasil yang tidak ideal yang mungkin menunjukkan masalah yang lebih dalam, tetapi tidak merusak fungsionalitas secara langsung.
* Pesan ``Info`` menunjukkan acara dan pembaruan status yang berfungsi sebagai verifikasi visual bahwa sistem berjalan seperti yang diharapkan.
* Pesan ``Debug`` merinci seluruh proses langkah demi langkah dari eksekusi sistem.

Level default adalah ``Info``.
Anda hanya akan melihat pesan dengan tingkat keseriusan default dan tingkat yang lebih parah.

Biasanya, hanya pesan ``Debug`` yang disembunyikan karena itu satu-satunya level yang tidak seserius ``Info``.
Misalnya, jika Anda menyetel level default ke ``Warn``, Anda hanya akan melihat pesan dengan tingkat keparahan ``Warn``, ``Error``, dan ``Fatal``.

3.1 Tetapkan level logger default
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Anda dapat menyetel level logger default saat pertama kali menjalankan node ``/turtlesim`` menggunakan pemetaan ulang.
Masukkan perintah berikut di terminal Anda:

.. blok kode :: konsol

     ros2 jalankan turtlesim turtlesim_node --ros-args --log-level WARN

Sekarang Anda tidak akan melihat pesan tingkat ``Info`` awal yang muncul di konsol terakhir kali Anda memulai ``turtlesim``.
Itu karena pesan ``Info`` berprioritas lebih rendah daripada keparahan default baru, ``Warn``.

Ringkasan
-------

``rqt_console`` dapat sangat membantu jika Anda perlu memeriksa dengan cermat pesan log dari sistem Anda.
Anda mungkin ingin memeriksa pesan log untuk sejumlah alasan, biasanya untuk mencari tahu di mana terjadi kesalahan dan rangkaian peristiwa yang mengarah ke sana.

Langkah selanjutnya
----------

Tutorial berikutnya akan mengajarkan Anda tentang memulai beberapa node sekaligus dengan :doc:`ROS 2 Launch <../Launching-Multiple-Nodes/Launching-Multiple-Nodes>`.