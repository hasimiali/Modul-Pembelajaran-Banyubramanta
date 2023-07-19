.. redirect-dari::

     Tutorial/Peluncuran-File/Menggunakan-ROS2-Peluncuran-untuk-Proyek-Besar
     Tutorial/Peluncuran/Menggunakan-ROS2-Peluncuran-untuk-Proyek-Besar

.. _MenggunakanROS2LaunchForLargeProjects:

Mengelola proyek-proyek besar
=======================

**Sasaran:** Pelajari praktik terbaik dalam mengelola proyek besar menggunakan file peluncuran ROS 2.

**Tingkat tutorial:** Menengah

**Waktu:** 20 menit

.. isi :: Isi
    :kedalaman: 3
    :lokal:

Latar belakang
----------

Tutorial ini menjelaskan beberapa tip untuk menulis file peluncuran untuk proyek besar.
Fokusnya adalah pada bagaimana menyusun file peluncuran sehingga dapat digunakan kembali sebanyak mungkin dalam situasi yang berbeda.
Selain itu, ini mencakup contoh penggunaan berbagai alat peluncuran ROS 2, seperti parameter, file YAML, pemetaan ulang, ruang nama, argumen default, dan konfigurasi RViz.

Prasyarat
-------------

Tutorial ini menggunakan :doc:`turtlesim <../../Beginner-CLI-Tools/Introducing-Turtlesim/Introducing-Turtlesim>` dan :doc:`turtle_tf2_py <../Tf2/Introduction-To-Tf2>` paket.
Tutorial ini juga menganggap Anda memiliki :doc:`membuat paket baru <../../Beginner-Client-Libraries/Creating-Your-First-ROS2-Package>` dari tipe build ``ament_python`` bernama ``launch_tutorial ``.

Perkenalan
------------

Aplikasi besar pada robot biasanya melibatkan beberapa node yang saling berhubungan, yang masing-masing dapat memiliki banyak parameter.
Simulasi beberapa kura-kura di simulator kura-kura bisa menjadi contoh yang baik.
Simulasi turtle terdiri dari beberapa node turtle, konfigurasi dunia, dan node penyiar dan pendengar TF.
Di antara semua node, terdapat sejumlah besar parameter ROS yang memengaruhi perilaku dan tampilan node ini.
File peluncuran ROS 2 memungkinkan kita untuk memulai semua node dan mengatur parameter yang sesuai di satu tempat.
Di akhir tutorial, Anda akan membuat file peluncuran ``launch_turtlesim_launch.py`` dalam paket ``launch_tutorial``.
File peluncuran ini akan memunculkan node berbeda yang bertanggung jawab untuk simulasi dua simulasi turtlesim, memulai penyiar dan pendengar TF, memuat parameter, dan meluncurkan konfigurasi RViz.
Dalam tutorial ini, kita akan membahas file peluncuran ini dan semua fitur terkait yang digunakan.

Menulis file peluncuran
--------------------

1 Organisasi tingkat atas
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Salah satu tujuan dalam proses penulisan file peluncuran adalah membuatnya dapat digunakan kembali sebanyak mungkin.
Ini dapat dilakukan dengan mengelompokkan node dan konfigurasi terkait ke dalam file peluncuran terpisah.
Setelah itu, file peluncuran tingkat atas yang didedikasikan untuk konfigurasi tertentu dapat ditulis.
Ini akan memungkinkan perpindahan antar robot identik dilakukan tanpa mengubah file peluncuran sama sekali.
Bahkan perubahan seperti berpindah dari robot sungguhan ke robot simulasi dapat dilakukan hanya dengan sedikit perubahan.

Kami sekarang akan membahas struktur file peluncuran tingkat atas yang memungkinkan hal ini.
Pertama, kami akan membuat file peluncuran yang akan memanggil file peluncuran terpisah.
Untuk melakukannya, mari buat file ``launch_turtlesim_launch.py`` di folder ``/launch`` dari paket ``launch_tutorial`` kita.

.. blok kode :: Python

    impor os

    dari ament_index_python.packages impor get_package_share_directory

    dari peluncuran impor LaunchDescription
    dari launch.actions impor SertakanLaunchDescription
    dari launch.launch_description_sources mengimpor PythonLaunchDescriptionSource


    def generate_launch_description():
       turtlesim_world_1 = SertakanLaunchDescription(
          PythonLaunchDescriptionSource([os.path.join(
             get_package_share_directory('launch_tutorial'), 'launch'),
             '/turtlesim_world_1_launch.py'])
          )
       turtlesim_world_2 = SertakanLaunchDescription(
          PythonLaunchDescriptionSource([os.path.join(
             get_package_share_directory('launch_tutorial'), 'launch'),
             '/turtlesim_world_2_launch.py'])
          )
       broadcaster_listener_nodes = SertakanLaunchDescription(
          PythonLaunchDescriptionSource([os.path.join(
             get_package_share_directory('launch_tutorial'), 'launch'),
             '/broadcaster_listener_launch.py']),
          launch_arguments={'target_frame': 'carrot1'}.items(),
          )
       mimik_node = SertakanLaunchDescription(
          PythonLaunchDescriptionSource([os.path.join(
             get_package_share_directory('launch_tutorial'), 'launch'),
             '/mimic_launch.py'])
          )
       fixed_frame_node = SertakanLaunchDescription(
          PythonLaunchDescriptionSource([os.path.join(
             get_package_share_directory('launch_tutorial'), 'launch'),
             '/fixed_broadcaster_launch.py'])
          )
       rviz_node = SertakanLaunchDescription(
          PythonLaunchDescriptionSource([os.path.join(
             get_package_share_directory('launch_tutorial'), 'launch'),
             '/turtlesim_rviz_launch.py'])
          )

       kembali LaunchDescription([
          turtlesim_world_1,
          turtlesim_world_2,
          broadcaster_listener_nodes,
          mimik_simpul,
          fixed_frame_node,
          rviz_node
       ])

File peluncuran ini menyertakan sekumpulan file peluncuran lainnya.
Masing-masing file peluncuran yang disertakan ini berisi node, parameter, dan mungkin, penyertaan bersarang, yang berkaitan dengan satu bagian sistem.
Tepatnya, kami meluncurkan dua dunia simulasi turtlesim, penyiar TF, pendengar TF, mimik, penyiar bingkai tetap, dan node RViz.

.. catatan:: Tip Desain: File peluncuran tingkat atas harus singkat, terdiri dari penyertaan ke file lain yang terkait dengan subkomponen aplikasi, dan parameter yang biasanya diubah.

Menulis file peluncuran dengan cara berikut memudahkan untuk menukar satu bagian dari sistem, seperti yang akan kita lihat nanti.
Namun, ada kalanya beberapa node atau file peluncuran harus diluncurkan secara terpisah karena alasan kinerja dan penggunaan.

.. catatan:: Kiat desain: Waspadai pengorbanan saat memutuskan berapa banyak file peluncuran tingkat atas yang diperlukan aplikasi Anda.

2 Parameter
^^^^^^^^^^^^^^

2.1 Mengatur parameter di file peluncuran
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kami akan mulai dengan menulis file peluncuran yang akan memulai simulasi turtlesim pertama kami.
Pertama, buat file baru bernama ``turtlesim_world_1_launch.py``.

.. blok kode :: Python

    dari peluncuran impor LaunchDescription
    dari launch.actions import DeclareLaunchArgument
    dari launch.substitutions import LaunchConfiguration, TextSubstitution

    dari launch_ros.actions impor Node


    def generate_launch_description():
       background_r_launch_arg = DeklarasikanLaunchArgument(
          'background_r', default_value=TeksSubstitusi(teks='0')
       )
       background_g_launch_arg = DeklarasikanLaunchArgument(
          'background_g', nilai_default=SubstitusiTeks(teks='84')
       )
       background_b_launch_arg = DeklarasikanLaunchArgument(
          'background_b', default_value=TeksSubstitusi(teks='122')
       )

       kembali LaunchDescription([
          background_r_launch_arg,
          background_g_launch_arg,
          background_b_launch_arg,
          Simpul(
             package='turtlesim',
             dapat dieksekusi='turtlesim_node',
             nama='sim',
             parameter=[{
                'background_r': LaunchConfiguration('background_r'),
                'background_g': LaunchConfiguration('background_g'),
                'background_b': LaunchConfiguration('background_b'),
             }]
          ),
       ])

File peluncuran ini memulai node ``turtlesim_node``, yang memulai simulasi turtlesim, dengan parameter konfigurasi simulasi yang ditentukan dan diteruskan ke node.

2.2 Memuat parameter dari file YAML
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pada peluncuran kedua, kita akan memulai simulasi turtlesim kedua dengan konfigurasi yang berbeda.
Sekarang buat file ``turtlesim_world_2_launch.py``.

.. blok kode :: Python

    impor os

    dari ament_index_python.packages impor get_package_share_directory

    dari peluncuran impor LaunchDescription
    dari launch_ros.actions impor Node


    def generate_launch_description():
       config = os.path.bergabung(
          get_package_share_directory('launch_tutorial'),
          'konfigurasi',
          'turtlesim.yaml'
          )

       kembali LaunchDescription([
          Simpul(
             package='turtlesim',
             dapat dieksekusi='turtlesim_node',
             namespace='turtlesim2',
             nama='sim',
             parameter=[konfigurasi]
          )
       ])

File peluncuran ini akan meluncurkan ``turtlesim_node`` yang sama dengan nilai parameter yang dimuat langsung dari file konfigurasi YAML.
Menentukan argumen dan parameter dalam file YAML memudahkan untuk menyimpan dan memuat sejumlah besar variabel.
Selain itu, file YAML dapat dengan mudah diekspor dari daftar ``ros2 param`` saat ini.
Untuk mempelajari cara melakukannya, lihat tutorial :doc:`Memahami parameter <../../Beginner-CLI-Tools/Understanding-ROS2-Parameters/Understanding-ROS2-Parameters>`.

Sekarang mari buat file konfigurasi, ``turtlesim.yaml``, di folder ``/config`` dari paket kita, yang akan dimuat oleh file peluncuran kita.

.. blok kode :: YAML

    /turtlesim2/sim:
       ros__parameter:
          background_b: 255
          background_g: 86
          background_r: 150

Jika sekarang kita memulai file peluncuran ``turtlesim_world_2_launch.py``, kita akan memulai ``turtlesim_node`` dengan warna latar yang telah dikonfigurasi sebelumnya.

Untuk mempelajari lebih lanjut tentang menggunakan parameter dan menggunakan file YAML, lihat tutorial :doc:`Understand parameter <../../Beginner-CLI-Tools/Understanding-ROS2-Parameters/Understanding-ROS2-Parameters>`.

2.3 Menggunakan wildcard dalam file YAML
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ada kalanya kita ingin mengatur parameter yang sama di lebih dari satu node.
Node ini dapat memiliki ruang nama atau nama yang berbeda tetapi masih memiliki parameter yang sama.
Mendefinisikan file YAML terpisah yang secara eksplisit mendefinisikan ruang nama dan nama node tidaklah efisien.
Solusinya adalah menggunakan karakter wildcard, yang bertindak sebagai pengganti karakter yang tidak dikenal dalam nilai teks, untuk menerapkan parameter ke beberapa node berbeda.

Sekarang mari kita buat ``turtlesim_world_3_launch.py`` serupa dengan ``turtlesim_world_2_launch.py`` untuk menyertakan satu lagi node ``turtlesim_node``.

.. blok kode :: Python

    ...
    Simpul(
       package='turtlesim',
       dapat dieksekusi='turtlesim_node',
       namespace='turtlesim3',
       nama='sim',
       parameter=[konfigurasi]
    )

Namun, memuat file YAML yang sama tidak akan memengaruhi tampilan dunia turtlesim ketiga.
Alasannya adalah parameternya disimpan di bawah namespace lain seperti yang ditunjukkan di bawah ini:

.. blok kode :: konsol

    /turtlesim3/sim:
       background_b
       background_g
       background_r

Oleh karena itu, daripada membuat konfigurasi baru untuk node yang sama yang menggunakan parameter yang sama, kita dapat menggunakan sintaks wildcard.
``/**`` akan menetapkan semua parameter di setiap node, terlepas dari perbedaan dalam nama node dan ruang nama.

Kami sekarang akan memperbarui ``turtlesim.yaml``, di folder ``/config`` dengan cara berikut:

.. blok kode :: YAML

    /**:
       ros__parameter:
          background_b: 255
          background_g: 86
          background_r: 150

Sekarang sertakan deskripsi peluncuran ``turtlesim_world_3_launch.py`` dalam file peluncuran utama kita.
Menggunakan file konfigurasi tersebut dalam deskripsi peluncuran kami akan menetapkan parameter ``background_b``, ``background_g``, dan ``background_r`` ke nilai yang ditentukan dalam node ``turtlesim3/sim`` dan ``turtlesim2/sim``.

3 ruang nama
^^^^^^^^^^^^^^

Seperti yang mungkin telah Anda ketahui, kami telah menentukan ruang nama untuk dunia turlesim di file ``turtlesim_world_2_launch.py``.
Ruang nama unik memungkinkan sistem untuk memulai dua node serupa tanpa konflik nama node atau nama topik.

.. blok kode :: Python

    namespace='turtlesim2',

Namun, jika file peluncuran berisi node dalam jumlah besar, menentukan ruang nama untuk masing-masing node dapat menjadi membosankan.
Untuk mengatasi masalah tersebut, tindakan ``PushROSNamespace`` dapat digunakan untuk menentukan namespace global untuk setiap deskripsi file peluncuran.
Setiap node bersarang akan mewarisi namespace tersebut secara otomatis.

Untuk melakukannya, pertama-tama, kita perlu menghapus baris ``namespace='turtlesim2'`` dari file ``turtlesim_world_2_launch.py``.
Setelah itu, kita perlu memperbarui ``launch_turtlesim_launch.py`` untuk menyertakan baris berikut:

.. blok kode :: Python

    dari launch.actions mengimpor GroupAction
    dari launch_ros.actions impor PushROSNamespace

       ...
       turtlesim_world_2 = SertakanLaunchDescription(
          PythonLaunchDescriptionSource([os.path.join(
             get_package_share_directory('launch_tutorial'), 'launch'),
             '/turtlesim_world_2_launch.py'])
          )
       turtlesim_world_2_with_namespace = GroupAction(
         tindakan=[
             PushROSNamespace('turtlesim2'),
             turtlesim_world_2,
          ]
       )

Terakhir, kami mengganti ``turtlesim_world_2`` menjadi ``turtlesim_world_2_with_namespace`` dalam pernyataan ``return LaunchDescription``.
Akibatnya, setiap node dalam deskripsi peluncuran ``turtlesim_world_2_launch.py`` akan memiliki namespace ``turtlesim2``.

4 Menggunakan kembali node
^^^^^^^^^^^^^^^^^^

Sekarang buat file ``broadcaster_listener_launch.py``.

.. blok kode :: Python

    dari peluncuran impor LaunchDescription
    dari launch.actions import DeclareLaunchArgument
    dari launch.substitutions import LaunchConfiguration

    dari launch_ros.actions impor Node


    def generate_launch_description():
       kembali LaunchDescription([
          DeklarasiLaunchArgument(
             'target_frame', default_value='turtle1',
             description='Nama bingkai target.'
          ),
          Simpul(
             paket='turtle_tf2_py',
             dapat dieksekusi='turtle_tf2_broadcaster',
             nama='penyiar1',
             parameter=[
                {'turtlename': 'turtle1'}
             ]
          ),
          Simpul(
             paket='turtle_tf2_py',
             dapat dieksekusi='turtle_tf2_broadcaster',
             nama='penyiar2',
             parameter=[
                {'turtlename': 'turtle2'}
             ]
          ),
          Simpul(
             paket='turtle_tf2_py',
             dapat dieksekusi='turtle_tf2_listener',
             nama='pendengar',
             parameter=[
                {'target_frame': LaunchConfiguration('target_frame')}
             ]
          ),
       ])


Dalam file ini, kami telah mendeklarasikan argumen peluncuran ``target_frame`` dengan nilai default ``turtle1``.
Nilai default berarti bahwa file peluncuran dapat menerima argumen untuk diteruskan ke node-nya, atau jika argumen tidak diberikan, ia akan meneruskan nilai default ke node-nya.

Setelah itu, kami menggunakan node ``turtle_tf2_broadcaster`` dua kali menggunakan nama dan parameter yang berbeda selama peluncuran.
Ini memungkinkan kami untuk menduplikasi simpul yang sama tanpa konflik.

Kami juga memulai node ``turtle_tf2_listener`` dan menetapkan parameter ``target_frame`` yang kami nyatakan dan peroleh di atas.

5 Parameter menimpa
^^^^^^^^^^^^^^^^^^^^^^^^^^

Ingatlah bahwa kami memanggil file ``broadcaster_listener_launch.py`` di file peluncuran tingkat atas kami.
Selain itu, kami telah memberikan argumen peluncuran ``target_frame`` seperti yang ditunjukkan bdi bawah:

.. blok kode :: Python

    broadcaster_listener_nodes = SertakanLaunchDescription(
       PythonLaunchDescriptionSource([os.path.join(
          get_package_share_directory('launch_tutorial'), 'launch'),
          '/broadcaster_listener_launch.py']),
       launch_arguments={'target_frame': 'carrot1'}.items(),
       )

Sintaks ini memungkinkan kita mengubah bingkai target sasaran default menjadi ``carrot1``.
Jika Anda ingin ``turtle2`` mengikuti ``turtle1`` alih-alih ``carrot1``, cukup hapus baris yang mendefinisikan ``launch_arguments``.
Ini akan menetapkan ``target_frame`` nilai defaultnya, yaitu ``turtle1``.

6 Pemetaan ulang
^^^^^^^^^^^^

Sekarang buat file ``mimic_launch.py``.

.. blok kode :: Python

    dari peluncuran impor LaunchDescription
    dari launch_ros.actions impor Node


    def generate_launch_description():
       kembali LaunchDescription([
          Simpul(
             package='turtlesim',
             dapat dieksekusi = 'meniru',
             nama='meniru',
             pemetaan ulang=[
                ('/input/pose', '/turtle2/pose'),
                ('/keluaran/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
             ]
          )
       ])

File peluncuran ini akan memulai node ``mimic``, yang akan memberikan perintah ke satu turtlesim untuk mengikuti yang lain.
Node dirancang untuk menerima pose target pada topik ``/input/pose``.
Dalam kasus kita, kita ingin memetakan ulang pose target dari topik ``/turtle2/pose``.
Terakhir, kami memetakan ulang topik ``/output/cmd_vel`` ke ``/turtlesim2/turtle1/cmd_vel``.
Dengan cara ini ``turtle1`` di dunia simulasi ``turtlesim2`` kita akan mengikuti ``turtle2`` di dunia simulasi turtlesim awal kita.

7 file konfigurasi
^^^^^^^^^^^^^^^^

Sekarang mari kita membuat file bernama ``turtlesim_rviz_launch.py``.

.. blok kode :: Python

    impor os

    dari ament_index_python.packages impor get_package_share_directory

    dari peluncuran impor LaunchDescription
    dari launch_ros.actions impor Node


    def generate_launch_description():
       rviz_config = os.path.bergabung(
          get_package_share_directory('turtle_tf2_py'),
          'rviz',
          'turtle_rviz.rviz'
          )

       kembali LaunchDescription([
          Simpul(
             paket='rviz2',
             dapat dieksekusi='rviz2',
             nama='rviz2',
             argumen=['-d', rviz_config]
          )
       ])

File peluncuran ini akan memulai RViz dengan file konfigurasi yang ditentukan dalam paket ``turtle_tf2_py``.
Konfigurasi RViz ini akan mengatur bingkai dunia, mengaktifkan visualisasi TF, dan memulai RViz dengan tampilan dari atas ke bawah.

8 Variabel Lingkungan
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sekarang mari buat file peluncuran terakhir bernama ``fixed_broadcaster_launch.py`` dalam paket kita.

.. blok kode :: Python

    dari peluncuran impor LaunchDescription
    dari launch.actions import DeclareLaunchArgument
    dari launch.substitutions import EnvironmentVariable, LaunchConfiguration
    dari launch_ros.actions impor Node


    def generate_launch_description():
       kembali LaunchDescription([
          DeklarasiLaunchArgument(
                'node_prefix',
                default_value=[Variabel Lingkungan('PENGGUNA'), '_'],
                description='awalan untuk nama node'
          ),
          Simpul(
                paket='turtle_tf2_py',
                dapat dieksekusi='fixed_frame_tf2_broadcaster',
                name=[LaunchConfiguration('node_prefix'), 'fixed_broadcaster'],
          ),
       ])

File peluncuran ini menunjukkan cara variabel lingkungan dapat dipanggil di dalam file peluncuran.
Variabel lingkungan dapat digunakan untuk mendefinisikan atau mendorong ruang nama untuk membedakan node pada komputer atau robot yang berbeda.

Menjalankan file peluncuran
--------------------

1 Perbarui setup.py
^^^^^^^^^^^^^^^^^^^^

Buka ``setup.py`` dan tambahkan baris berikut sehingga file peluncuran dari folder ``launch/`` dan file konfigurasi dari ``config/`` akan diinstal.
Kolom ``data_files`` sekarang akan terlihat seperti ini:

.. blok kode :: Python

    file_data=[
          ...
          (os.path.join('berbagi', nama_paket, 'luncurkan'),
             glob(os.path.join('peluncuran', '*peluncuran.[pxy][yma]*'))),
          (os.path.join('berbagi', nama_paket, 'config'),
             glob(os.path.join('config', '*.yaml'))),
       ],

2 Bangun dan jalankan
^^^^^^^^^^^^^^^^^^

Untuk akhirnya melihat hasil dari kode kita, buat paket dan luncurkan file peluncuran tingkat atas menggunakan perintah berikut:

.. blok kode :: konsol

    peluncuran ros2 launch_tutorial launch_turtlesim_launch.py

Anda sekarang akan melihat dua simulasi turtlesim dimulai.
Ada dua kura-kura di yang pertama dan satu di yang kedua.
Dalam simulasi pertama, ``turtle2`` muncul di bagian kiri bawah dunia.
Tujuannya adalah untuk mencapai bingkai ``carrot1`` yang jaraknya lima meter pada sumbu x relatif terhadap bingkai ``turtle1``.

``turtlesim2/turtle1`` di bagian kedua dirancang untuk meniru perilaku ``turtle2``.

Jika Anda ingin mengontrol ``turtle1``, jalankan teleop node.

.. blok kode :: konsol

    ros2 jalankan turtlesim turtle_teleop_key

Hasilnya, Anda akan melihat gambar serupa:

.. gambar:: gambar/turtlesim_worlds.png

Selain itu, RViz seharusnya sudah mulai.
Ini akan menampilkan semua bingkai turtle relatif terhadap bingkai ``dunia``, yang asalnya ada di pojok kiri bawah.

.. gambar:: gambar/turtlesim_rviz.png

Ringkasan
-------

Dalam tutorial ini, Anda belajar tentang berbagai tip dan praktik mengelola proyek besar menggunakan file peluncuran ROS 2.