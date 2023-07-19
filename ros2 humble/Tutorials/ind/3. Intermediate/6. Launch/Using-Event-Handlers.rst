.. redirect-dari::

     Tutorial/Launch-Files/Menggunakan-Event-Handlers
     Tutorial/Peluncuran/Menggunakan-Event-Handlers

Menggunakan event handler
====================

**Sasaran:** Pelajari tentang pengendali peristiwa di file peluncuran ROS 2

**Tingkat tutorial:** Menengah

**Waktu:** 15 menit

.. isi :: Daftar Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

Peluncuran di ROS 2 adalah sistem yang menjalankan dan mengelola proses yang ditentukan pengguna.
Ini bertanggung jawab untuk memantau status proses yang diluncurkannya, serta melaporkan dan bereaksi terhadap perubahan status proses tersebut.
Perubahan ini disebut event dan dapat ditangani dengan mendaftarkan event handler dengan sistem peluncuran.
Penangan acara dapat didaftarkan untuk acara tertentu dan dapat berguna untuk memantau keadaan proses.
Selain itu, mereka dapat digunakan untuk menentukan seperangkat aturan kompleks yang dapat digunakan untuk memodifikasi file peluncuran secara dinamis.

Tutorial ini menunjukkan contoh penggunaan event handler di file peluncuran ROS 2.

Prasyarat
-------------

Tutorial ini menggunakan paket :doc:`turtlesim <../../Beginner-CLI-Tools/Introducing-Turtlesim/Introducing-Turtlesim>`.
Tutorial ini juga menganggap Anda memiliki :doc:`membuat paket baru <../../Beginner-Client-Libraries/Creating-Your-First-ROS2-Package>` dari tipe build ``ament_python`` bernama ``launch_tutorial ``.

Tutorial ini memperluas kode yang ditampilkan di tutorial :doc:`Using substitutions in launch files <./Using-Substitutions>`.

Menggunakan event handler
--------------------

1 Contoh file peluncuran event handler
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Buat file baru bernama file ``example_event_handlers_launch.py`` di folder ``launch`` dari paket ``launch_tutorial``.

.. blok kode :: python

     dari launch_ros.actions impor Node

     dari peluncuran impor LaunchDescription
     dari launch.actions import (DeclareLaunchArgument, EmitEvent, ExecuteProcess,
                                 LogInfo, RegisterEventHandler, TimerAction)
     dari launch.conditions mengimpor IfCondition
     dari launch.event_handlers import (OnExecutionComplete, OnProcessExit,
                                     OnProcessIO, OnProcessStart, OnShutdown)
     dari launch.events impor Shutdown
     dari launch.substitutions import (EnvironmentVariable, FindExecutable,
                                     LaunchConfiguration, LocalSubstitusi,
                                     Ekspresi Python)


     def generate_launch_description():
         turtlesim_ns = LaunchConfiguration('turtlesim_ns')
         use_provided_red = LaunchConfiguration('use_provided_red')
         new_background_r = LaunchConfiguration('new_background_r')

         turtlesim_ns_launch_arg = DeklarasikanLaunchArgument(
             'turtlesim_ns',
             default_value='turtlesim1'
         )
         use_provided_red_launch_arg = DeklarasikanLaunchArgument(
             'use_provided_red',
             default_value='Salah'
         )
         new_background_r_launch_arg = DeklarasikanLaunchArgument(
             'new_background_r',
             default_value='200'
         )

         turtlesim_node = Node(
             package='turtlesim',
             namespace=turtlesim_ns,
             dapat dieksekusi='turtlesim_node',
             nama='sim'
         )
         spawn_turtle = Jalankan Proses(
             cmd=[[
                 FindExecutable(nama='ros2'),
                 ' layanan panggilan ',
                 turtlesim_ns,
                 '/muncul ',
                 'turtlesim/srv/Spawn ',
                 '"{x: 2, y: 2, teta: 0,2}"'
             ]],
             cangkang=Benar
         )
         change_background_r = Jalankan Proses(
             cmd=[[
                 FindExecutable(nama='ros2'),
                 'set parameter',
                 turtlesim_ns,
                 '/sim background_r',
                 '120'
             ]],
             cangkang=Benar
         )
         change_background_r_conditioned = Jalankan Proses(
             kondisi=JikaKondisi(
                 Ekspresi Python([
                     baru_latar belakang_r,
                     ' == 200',
                     ' Dan ',
                     use_provided_red
                 ])
             ),
             cmd=[[
                 FindExecutable(nama='ros2'),
                 'set parameter',
                 turtlesim_ns,
                 '/sim background_r',
                 new_background_r
             ]],
             cangkang=Benar
         )

         kembali LaunchDescription([
             turtlesim_ns_launch_arg,
             gunakan_provided_red_launch_arg,
             new_background_r_launch_arg,
             turtlesim_node,
             DaftarEventHandler(
                 OnProcessStart(
                     target_action=turtlesim_node,
                     saat_mulai=[
                         LogInfo(msg='Turtlesim dimulai, penyu bertelur'),
                         spawn_turtle
                     ]
                 )
             ),
             DaftarEventHandler(
                 OnProcessIO(
                     target_action=spawn_turtle,on_stdout=lambda acara: LogInfo(
                         msg='Memunculkan permintaan mengatakan "{}"'.format(
                             acara.text.decode().strip())
                     )
                 )
             ),
             DaftarEventHandler(
                 OnExecutionComplete(
                     target_action=spawn_turtle,
                     on_completion=[
                         LogInfo(msg='Spawn selesai'),
                         ubah_latar belakang_r,
                         TimerAksi(
                             periode=2,0,
                             tindakan=[ubah_latar belakang_r_dikondisikan],
                         )
                     ]
                 )
             ),
             DaftarEventHandler(
                 OnProcessExit(
                     target_action=turtlesim_node,
                     on_exit=[
                         LogInfo(msg=(Variabel Lingkungan(nama='PENGGUNA'),
                                 ' tutup jendela turtlesim')),
                         EmitEvent(event=Shutdown(
                             alasan='Jendela ditutup'))
                     ]
                 )
             ),
             DaftarEventHandler(
                 Saat Mati(
                     on_shutdown=[Info Log(
                         msg=['Luncurkan diminta untuk mematikan: ',
                             Substitusi Lokal('event.reason')]
                     )]
                 )
             ),
         ])

Tindakan ``RegisterEventHandler`` untuk peristiwa ``OnProcessStart``, ``OnProcessIO``, ``OnExecutionComplete``, ``OnProcessExit``, dan ``OnShutdown`` ditentukan dalam deskripsi peluncuran.

Event handler ``OnProcessStart`` digunakan untuk mendaftarkan fungsi callback yang dijalankan saat node turtlesim dimulai.
Ini mencatat pesan ke konsol dan mengeksekusi aksi ``spawn_turtle`` ketika simpul turtlesim dimulai.

.. blok kode :: python

     DaftarEventHandler(
         OnProcessStart(
             target_action=turtlesim_node,
             saat_mulai=[
                 LogInfo(msg='Turtlesim dimulai, penyu bertelur'),
                 spawn_turtle
             ]
         )
     ),

Event handler ``OnProcessIO`` digunakan untuk mendaftarkan fungsi panggilan balik yang dijalankan saat aksi ``spawn_turtle`` menulis ke output standarnya.
Ini mencatat hasil dari permintaan spawn.

.. blok kode :: python

     DaftarEventHandler(
         OnProcessIO(
             target_action=spawn_turtle,
             on_stdout=lambda acara: LogInfo(
                 msg='Memunculkan permintaan mengatakan "{}"'.format(
                     acara.text.decode().strip())
             )
         )
     ),

Event handler ``OnExecutionComplete`` digunakan untuk mendaftarkan fungsi callback yang dijalankan saat aksi ``spawn_turtle`` selesai.
Ini mencatat pesan ke konsol dan mengeksekusi tindakan ``change_background_r`` dan ``change_background_r_conditioned`` saat tindakan spawn selesai.

.. blok kode :: python

     DaftarEventHandler(
         OnExecutionComplete(
             target_action=spawn_turtle,
             on_completion=[
                 LogInfo(msg='Spawn selesai'),
                 ubah_latar belakang_r,
                 TimerAksi(
                     periode=2,0,
                     tindakan=[ubah_latar belakang_r_dikondisikan],
                 )
             ]
         )
     ),

Event handler ``OnProcessExit`` digunakan untuk mendaftarkan fungsi callback yang dijalankan saat node turtlesim keluar.
Itu mencatat pesan ke konsol dan mengeksekusi tindakan ``EmitEvent`` untuk memancarkan peristiwa ``Shutdown`` ketika simpul turtlesim keluar.
Artinya proses peluncuran akan terhenti ketika jendela turtlesim ditutup.

.. blok kode :: python

     DaftarEventHandler(
         OnProcessExit(
             target_action=turtlesim_node,
             on_exit=[
                 LogInfo(msg=(Variabel Lingkungan(nama='PENGGUNA'),
                         ' tutup jendela turtlesim')),
                 EmitEvent(event=Shutdown(
                     alasan='Jendela ditutup'))
             ]
         )
     ),

Terakhir, event handler ``OnShutdown`` digunakan untuk mendaftarkan fungsi panggilan balik yang dijalankan saat file peluncuran diminta untuk dimatikan.
Itu mencatat pesan ke konsol mengapa file peluncuran diminta untuk dimatikan.
Itu mencatat pesan dengan alasan untuk dimatikan seperti penutupan jendela turtlesim atau :kbd:`ctrl-c` sinyal yang dibuat oleh pengguna.

.. blok kode :: python

     DaftarEventHandler(
         Saat Mati(
             on_shutdown=[Info Log(
                 msg=['Luncurkan diminta untuk mematikan: ',
                     Substitusi Lokal('event.reason')]
             )]
         )
     ),

Membangun paket
-----------------

Pergi ke akar ruang kerja, dan buat paketnya:

.. blok kode :: konsol

   membangun colcon

Ingat juga untuk sumber ruang kerja setelah membangun.

Contoh peluncuran
-----------------

Sekarang Anda dapat meluncurkan file ``example_event_handlers_launch.py`` menggunakan perintah ``ros2 launch``.

.. blok kode :: konsol

     peluncuran ros2 launch_tutorial example_event_handlers_launch.py turtlesim_ns:='turtlesim3' use_provided_red:='True' new_background_r:=200

Ini akan melakukan hal berikut:

#. Mulai simpul turtlesim dengan latar belakang biru
#. Menelurkan kura-kura kedua
#. Ubah warnanya menjadi ungu
#. Ubah warna menjadi merah muda setelah dua detik jika argumen ``background_r`` yang diberikan adalah ``200`` dan argumen ``use_provided_red`` adalah ``True``
#. Matikan file peluncuran saat jendela turtlesim ditutup

Selain itu, ini akan mencatat pesan ke konsol saat:

#. Node turtlesim dimulai
#. Tindakan spawn dijalankan
#. Tindakan ``change_background_r`` dijalankan
#. Aksi ``change_background_r_conditioned`` dijalankan
#. Node turtlesim keluar
#. Proses peluncuran diminta untuk dimatikan.

Dokumentasi
-------------

`Dokumentasi peluncuran <https://github.com/ros2/launch/blob/{REPOS_FILE_BRANCH}/launch/doc/source/architecture.rst>`_ memberikan informasi mendetail tentang penangan peristiwa yang tersedia.

Ringkasan
-------

Dalam tutorial ini, Anda belajar tentang menggunakan event handler di file peluncuran.
Anda belajar tentang sintaks dan contoh penggunaannya untuk menentukan seperangkat aturan kompleks untuk memodifikasi file peluncuran secara dinamis.