.. redirect-dari::

     Tutorial/Tindakan/Menulis-a-Py-Action-Server-Client

.. _ActionsPy:

Menulis server tindakan dan klien (Python)
========================================

**Sasaran:** Mengimplementasikan server tindakan dan klien dengan Python.

**Tingkat tutorial:** Menengah

**Waktu:** 15 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Tindakan adalah bentuk komunikasi asinkron di ROS 2.
*Klien tindakan* mengirim permintaan sasaran ke *server tindakan*.
*Server tindakan* mengirimkan umpan balik tujuan dan hasil ke *klien tindakan*.

Prasyarat
-------------

Anda memerlukan paket ``custom_action_interfaces`` dan ``Fibonacci.action``
antarmuka yang ditentukan dalam tutorial sebelumnya, :doc:`../Creating-an-Action`.

Tugas
-----

1 Menulis server tindakan
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Mari fokus menulis server aksi yang menghitung deret Fibonacci
menggunakan tindakan yang kita buat di tutorial :doc:`../Creating-an-Action`.

Hingga saat ini, Anda telah membuat paket dan menggunakan ``ros2 run`` untuk menjalankan node Anda.
Namun, agar tetap sederhana dalam tutorial ini, kami akan membatasi server tindakan ke satu file.
Jika Anda ingin melihat seperti apa paket lengkap untuk tutorial tindakan, lihat
`action_tutorials <https://github.com/ros2/demos/tree/{REPOS_FILE_BRANCH}/action_tutorials>`__.

Buka file baru di direktori home Anda, sebut saja ``fibonacci_action_server.py``,
dan tambahkan kode berikut:

.. literalinclude:: scripts/server_0.py
     : bahasa: python

Baris 8 mendefinisikan kelas ``FibonacciActionServer`` yang merupakan subkelas dari ``Node``.
Kelas diinisialisasi dengan memanggil konstruktor ``Node``, menamai node kami ``fibonacci_action_server``:

.. literalinclude:: scripts/server_0.py
     : bahasa: python
     :baris: 11

Di konstruktor kami juga memberi contoh server tindakan baru:

.. literalinclude:: scripts/server_0.py
     : bahasa: python
     :baris: 12-16

Server tindakan memerlukan empat argumen:

1. Node ROS 2 untuk menambahkan klien tindakan ke: ``self``.
2. Jenis tindakan: ``Fibonacci`` (diimpor di baris 5).
3. Nama tindakan: ``'fibonacci'``.
4. Fungsi panggilan balik untuk mengeksekusi tujuan yang diterima: ``self.execute_callback``.
    Callback ini **harus** menampilkan pesan hasil untuk jenis tindakan.

Kami juga mendefinisikan metode ``execute_callback`` di kelas kami:

.. literalinclude:: scripts/server_0.py
     : bahasa: python
     :baris: 18-21

Ini adalah metode yang akan dipanggil untuk mengeksekusi tujuan setelah diterima.

Mari coba jalankan server tindakan kami:

.. tab::

   .. grup-tab :: Linux

     .. blok kode :: bash

       python3 fibonacci_action_server.py

   .. grup-tab :: macOS

     .. blok kode :: bash

       python3 fibonacci_action_server.py

   .. grup-tab :: Windows

     .. blok kode :: bash

       python fibonacci_action_server.py

Di terminal lain, kita bisa menggunakan antarmuka baris perintah untuk mengirim tujuan:

.. blok kode :: bash

     tindakan ros2 send_goal fibonacci custom_action_interfaces/action/Fibonacci "{urutan: 5}"

Di terminal yang menjalankan server tindakan, Anda akan melihat pesan log "Executing goal..." diikuti dengan peringatan bahwa status tujuan tidak disetel.
Secara default, jika status pegangan sasaran tidak disetel dalam callback eksekusi, status tersebut dianggap *dibatalkan*.

Kita dapat menggunakan metode `succeed() <http://docs.ros2.org/latest/api/rclpy/api/actions.html#rclpy.action.server.ServerGoalHandle.succeed>`_ pada pegangan tujuan untuk menunjukkan bahwa tujuannya berhasil:

.. literalinclude:: scripts/server_1.py
     : bahasa: python
     :baris: 18-22
     :tekankan-baris: 3

Sekarang jika Anda me-restart server tindakan dan mengirim tujuan lain, Anda akan melihat tujuan selesai dengan status ``SUCCEEDED``.

Sekarang mari kita buat eksekusi tujuan kita benar-benar menghitung dan mengembalikan deret Fibonacci yang diminta:

.. literalinclude:: scripts/server_2.py
     : bahasa: python
     :baris: 18-30
     :tekankan-baris: 4-7,12

Setelah menghitung urutannya, kami menetapkannya ke bidang pesan hasil sebelum kembali.

Sekali lagi, restart server tindakan dan kirim tujuan lain.
Anda harus melihat tujuan selesai dengan urutan hasil yang tepat.

1.2 Menerbitkan umpan balik
~~~~~~~~~~~~~~~~~~~~~~~~~

Salah satu hal yang menyenangkan tentang tindakan adalah kemampuan untuk memberikan umpan balik kepada klien tindakan selama eksekusi tujuan.
Kita dapat membuat server tindakan kita memublikasikan umpan balik untuk klien tindakan dengan memanggil `publish_feedback() gagang tujuan <http://docs.ros2.org/latest/api/rclpy/api/actions.html#rclpy.action.server.ServerGoalHandle .publish_feedback>`_ metode.

Kami akan mengganti variabel ``sequence``, dan menggunakan pesan umpan balik untuk menyimpan urutannya.
Setelah setiap pembaruan pesan umpan balik di for-loop, kami menerbitkan pesan umpan balik dan tidur untuk efek dramatis:

.. literalinclude:: scripts/server_3.py
     : bahasa: python
     : garis-penekanan: 1,23,24,27-31,36

Setelah memulai ulang server tindakan, kami dapat mengonfirmasi bahwa umpan balik sekarang dipublikasikan dengan menggunakan alat baris perintah dengan opsi ``--feedback``:

.. kode-blok::