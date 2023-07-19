.. redirect-dari::

     Tutorial/Launch-Files/Menggunakan-Substitusi
     Tutorial/Peluncuran/Menggunakan-Pergantian

Menggunakan substitusi
===================

**Sasaran:** Pelajari tentang penggantian dalam file peluncuran ROS 2.

**Tingkat tutorial:** Menengah

**Waktu:** 15 menit

.. isi :: Daftar Isi
    :kedalaman: 2
    :lokal:

Latar belakang
----------

File peluncuran digunakan untuk memulai node, layanan, dan menjalankan proses.
Serangkaian tindakan ini mungkin memiliki argumen, yang memengaruhi perilaku mereka.
Pergantian dapat digunakan dalam argumen untuk memberikan lebih banyak fleksibilitas saat mendeskripsikan file peluncuran yang dapat digunakan kembali.
Pergantian adalah variabel yang hanya dievaluasi selama pelaksanaan deskripsi peluncuran dan dapat digunakan untuk memperoleh informasi spesifik seperti konfigurasi peluncuran, variabel lingkungan, atau untuk mengevaluasi ekspresi Python yang sewenang-wenang.

Tutorial ini menunjukkan contoh penggunaan substitusi dalam file peluncuran ROS 2.

Prasyarat
-------------

Tutorial ini menggunakan paket :doc:`turtlesim <../../Beginner-CLI-Tools/Introducing-Turtlesim/Introducing-Turtlesim>`.
Tutorial ini juga menganggap Anda sudah familiar dengan :doc:`membuat paket <../../Beginner-Client-Libraries/Creating-Your-First-ROS2-Package>`.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../../Beginner-CLI-Tools/Configuring-ROS2-Environment>`.

Menggunakan substitusi
-------------------

1 Buat dan atur paket
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Buat paket baru tipe_build ``ament_python`` bernama ``launch_tutorial``:

.. blok kode :: konsol

   ros2 pkg buat launch_tutorial --build-type ament_python

Di dalam paket itu, buat direktori bernama ``launch``:

.. tab::

   .. grup-tab :: Linux

     .. blok kode :: bash

       mkdir launch_tutorial/launch

   .. grup-tab :: macOS

     .. blok kode :: bash

       mkdir launch_tutorial/launch

   .. grup-tab :: Windows

     .. blok kode :: bash

       md launch_tutorial/launch

Terakhir, pastikan untuk menambahkan perubahan pada ``setup.py`` paket sehingga file peluncuran akan diinstal:

.. blok kode :: python

   impor os
   dari glob impor glob
   dari setuptools import find_packages, setup

   nama_paket = 'peluncuran_tutorial'

   mempersiapkan(
       # Parameter lain ...
       file_data=[
           # ... File data lainnya
           # Sertakan semua file peluncuran.
           (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*')))
       ]
   )


2 File peluncuran induk
^^^^^^^^^^^^^^^^^^^^^^^^

Mari buat file peluncuran yang akan memanggil dan meneruskan argumen ke file peluncuran lainnya.
Untuk melakukannya, buat file ``example_main_launch.py`` di folder ``launch`` dari paket ``launch_tutorial``.

.. blok kode :: python

     dari launch_ros.substitutions impor FindPackageShare

     dari peluncuran impor LaunchDescription
     dari launch.actions impor SertakanLaunchDescription
     dari launch.launch_description_sources mengimpor PythonLaunchDescriptionSource
     dari launch.substitutions import PathJoinSubstitution, TextSubstitution


     def generate_launch_description():
         warna = {
             'background_r': '200'
         }

         kembali LaunchDescription([
             SertakanDeskripsiPeluncuran(
                 PythonLaunchDescriptionSumber([
                     PathJoinSubstitusi([
                         FindPackageShare('launch_tutorial'),
                         'meluncurkan',
                         'example_substitutions_launch.py'
                     ])
                 ]),
                 launch_arguments={
                     'turtlesim_ns': 'turtlesim2',
                     'use_provided_red': 'Benar',
                     'new_background_r': TextSubstitution(text=str(colors['background_r']))
                 }.item()
             )
         ])


Dalam file ``example_main_launch.py``, substitusi ``FindPackageShare`` digunakan untuk menemukan path ke paket ``launch_tutorial``.
Substitusi ``PathJoinSubstitution`` kemudian digunakan untuk menggabungkan jalur ke jalur paket tersebut dengan nama file ``example_substitutions_launch.py``.

.. blok kode :: python

     PathJoinSubstitusi([
         FindPackageShare('launch_tutorial'),
         'meluncurkan',
         'example_substitutions_launch.py'
     ])

Kamus ``launch_arguments`` dengan argumen ``turtlesim_ns`` dan ``use_provided_red`` diteruskan ke tindakan ``IncludeLaunchDescription``.
Substitusi ``TextSubstitution`` digunakan untuk mendefinisikan argumen ``new_background_r`` dengan nilai kunci ``background_r`` dalam kamus ``colors``.

.. blok kode :: python

     launch_arguments={
         'turtlesim_ns': 'turtlesim2',
         'use_provided_red': 'Benar',
         'new_background_r': TextSubstitution(text=str(colors['background_r']))
     }.item()

3 Pergantian contoh file peluncuran
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sekarang buat file ``example_substitutions_launch.py`` di folder yang sama.

.. blok kode :: python

     dari launch_ros.actions impor Node

     dari peluncuran impor LaunchDdeskripsi
     dari launch.actions impor DeclareLaunchArgument, ExecuteProcess, TimerAction
     dari launch.conditions mengimpor IfCondition
     dari launch.substitutions import LaunchConfiguration, PythonExpression


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
                 'panggilan layanan ros2',
                 turtlesim_ns,
                 '/muncul ',
                 'turtlesim/srv/Spawn ',
                 '"{x: 2, y: 2, teta: 0,2}"'
             ]],
             cangkang=Benar
         )
         change_background_r = Jalankan Proses(
             cmd=[[
                 'set parameter ros2',
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
                 'set parameter ros2',
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
             bertelur_kura-kura,
             ubah_latar belakang_r,
             TimerAksi(
                 periode=2,0,
                 tindakan=[ubah_latar belakang_r_dikondisikan],
             )
         ])

Dalam file ``example_substitutions_launch.py``, konfigurasi peluncuran ``turtlesim_ns``, ``use_provided_red``, dan ``new_background_r`` ditentukan.
Mereka digunakan untuk menyimpan nilai argumen peluncuran dalam variabel di atas dan meneruskannya ke tindakan yang diperlukan.
Substitusi ``LaunchConfiguration`` ini memungkinkan kita memperoleh nilai argumen peluncuran di bagian mana pun dari deskripsi peluncuran.

``DeclareLaunchArgument`` digunakan untuk menentukan argumen peluncuran yang dapat diteruskan dari file peluncuran di atas atau dari konsol.

.. blok kode :: python

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

Node ``turtlesim_node`` dengan ``namespace`` disetel ke substitusi ``turtlesim_ns`` ``LaunchConfiguration`` telah ditentukan.

.. blok kode :: python

     turtlesim_node = Node(
         package='turtlesim',
         namespace=turtlesim_ns,
         dapat dieksekusi='turtlesim_node',
         nama='sim'
     )

Setelah itu, tindakan ``ExecuteProcess`` yang disebut ``spawn_turtle`` ditentukan dengan argumen ``cmd`` yang sesuai.
Perintah ini membuat panggilan ke layanan spawn dari node turtlesim.

Selain itu, substitusi ``LaunchConfiguration`` digunakan untuk mendapatkan nilai argumen peluncuran ``turtlesim_ns`` untuk membuat string perintah.

.. blok kode :: python

     spawn_turtle = Jalankan Proses(
         cmd=[[
             'panggilan layanan ros2',
             turtlesim_ns,
             '/muncul ',
             'turtlesim/srv/Spawn ',
             '"{x: 2, y: 2, teta: 0,2}"'
         ]],
         cangkang=Benar
     )

Pendekatan yang sama digunakan untuk tindakan ``change_background_r`` dan ``change_background_r_conditioned`` yang mengubah parameter warna merah latar belakang turtlesim.
Perbedaannya adalah bahwa tindakan ``change_background_r_conditioned`` hanya dijalankan jika argumen ``new_background_r`` yang diberikan sama dengan ``200`` dan argumen peluncuran ``use_provided_red`` disetel ke ``True``.
Evaluasi di dalam ``IfCondition`` dilakukan dengan menggunakan substitusi ``PythonExpression``.

.. blok kode :: python

     change_background_r = Jalankan Proses(
         cmd=[['set parameter ros2',
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
             'set parameter ros2',
             turtlesim_ns,
             '/sim background_r',
             new_background_r
         ]],
         cangkang=Benar
     )

4 Bangun paket
^^^^^^^^^^^^^^^^^^^^^^^

Pergi ke akar ruang kerja, dan buat paketnya:

.. blok kode :: konsol

   membangun colcon

Ingat juga untuk sumber ruang kerja setelah membangun.

Contoh peluncuran
-----------------

Sekarang Anda dapat meluncurkan file ``example_main_launch.py`` menggunakan perintah ``ros2 launch``.

.. blok kode :: konsol

     peluncuran ros2 launch_tutorial example_main_launch.py

Ini akan melakukan hal berikut:

#. Mulai simpul turtlesim dengan latar belakang biru
#. Menelurkan kura-kura kedua
#. Ubah warnanya menjadi ungu
#. Ubah warna menjadi merah muda setelah dua detik jika argumen ``background_r`` yang diberikan adalah ``200`` dan argumen ``use_provided_red`` adalah ``True``

Memodifikasi argumen peluncuran
--------------------------

Jika Anda ingin mengubah argumen peluncuran yang disediakan, Anda dapat memperbaruinya di kamus ``launch_arguments`` di ``example_main_launch.py`` atau meluncurkan ``example_substitutions_launch.py`` dengan argumen pilihan.
Untuk melihat argumen yang mungkin diberikan ke file peluncuran, jalankan perintah berikut:

.. blok kode :: konsol

     peluncuran ros2 launch_tutorial example_substitutions_launch.py --show-args

Ini akan menampilkan argumen yang mungkin diberikan ke file peluncuran dan nilai defaultnya.

.. blok kode :: konsol

     Argumen (berikan argumen sebagai '<nama>:=<nilai>'):

         'turtlesim_ns':
             tidak ada deskripsi yang diberikan
             (default: 'turtlesim1')

         'use_provided_red':
             tidak ada deskripsi yang diberikan
             (default: 'Salah')

         'new_background_r':
             tidak ada deskripsi yang diberikan
             (bawaan: '200')

Sekarang Anda dapat meneruskan argumen yang diinginkan ke file peluncuran sebagai berikut:

.. blok kode :: konsol

     peluncuran ros2 launch_tutorial example_substitutions_launch.py turtlesim_ns:='turtlesim3' use_provided_red:='True' new_background_r:=200


Dokumentasi
-------------

`Dokumentasi peluncuran <https://github.com/ros2/launch/blob/{REPOS_FILE_BRANCH}/launch/doc/source/architecture.rst>`_ memberikan informasi mendetail tentang substitusi yang tersedia.

Ringkasan
-------

Dalam tutorial ini, Anda belajar tentang penggunaan substitusi dalam file peluncuran.
Anda mempelajari tentang kemungkinan dan kemampuannya untuk membuat file peluncuran yang dapat digunakan kembali.

Anda sekarang dapat mempelajari lebih lanjut tentang :doc:`menggunakan event handler dalam file peluncuran <./Using-Event-Handlers>` yang digunakan untuk menentukan seperangkat aturan kompleks yang dapat digunakan untuk memodifikasi file peluncuran secara dinamis.