Mengintegrasikan file peluncuran ke dalam paket ROS 2
========================================

**Sasaran:** Menambahkan file peluncuran ke paket ROS 2

**Tingkat tutorial:** Menengah

**Waktu:** 10 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Prasyarat
-------------

Anda seharusnya sudah membaca tutorial tentang cara :doc:`membuat paket ROS 2 <../../Beginner-Client-Libraries/Creating-Your-First-ROS2-Package>`.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../../Beginner-CLI-Tools/Configuring-ROS2-Environment>`.

Latar belakang
----------

Dalam :doc:`tutorial sebelumnya <Membuat-Launch-Files>`, kita melihat cara menulis file peluncuran yang berdiri sendiri.
Tutorial ini akan menunjukkan cara menambahkan file peluncuran ke paket yang sudah ada, dan konvensi yang biasanya digunakan.

Tugas
-----

1 Buat paket
^^^^^^^^^^^^^^^^^^^^^^

Buat ruang kerja untuk paket tempat tinggal:

.. tab::

   .. grup-tab :: Linux

     .. blok kode :: bash

       mkdir -p launch_ws/src
       cd peluncuran_ws/src

   .. grup-tab :: macOS

     .. blok kode :: bash

       mkdir -p launch_ws/src
       cd peluncuran_ws/src

   .. grup-tab :: Windows

     .. blok kode :: bash

       md launch_ws\src
       cd peluncuran_ws\src

.. tab::

   .. grup-tab:: Paket Python

     .. blok kode :: konsol

       ros2 pkg buat py_launch_example --build-type ament_python

   .. grup-tab:: Paket C++

     .. blok kode :: konsol

       ros2 pkg buat cpp_launch_example --build-type ament_cmake

2 Membuat struktur untuk menyimpan file peluncuran
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Secara konvensi, semua file peluncuran untuk sebuah paket disimpan di direktori ``launch`` di dalam paket.
Pastikan untuk membuat direktori ``launch`` di tingkat atas paket yang Anda buat di atas.

.. tab::

   .. grup-tab:: Paket Python

     Untuk paket Python, direktori yang berisi paket Anda akan terlihat seperti ini:

     .. blok kode :: konsol

       src/
         py_launch_example/
           meluncurkan/
           paket.xml
           py_launch_example/
           sumber/
           setup.cfg
           setup.py
           tes/

     Agar colcon menemukan file peluncuran, kita perlu memberi tahu alat penyiapan Python tentang file peluncuran kita menggunakan parameter ``data_files`` dari ``setup``.

     Di dalam file ``setup.py`` kita:

     .. blok kode :: python

       impor os
       dari glob impor glob
       dari setuptools import find_packages, setup

       package_name = 'py_launch_example'

       mempersiapkan(
           # Parameter lain ...
           file_data=[
               # ... File data lainnya
               # Sertakan semua file peluncuran.
               (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*')))
           ]
       )

   .. grup-tab:: Paket C++

     Untuk paket C++, kami hanya akan menyesuaikan file ``CMakeLists.txt`` dengan menambahkan:

     .. blok kode :: cmake

       # Instal file peluncuran.
       instal (DIRECTORY
         meluncurkan
         DESTINATION berbagi/${PROJECT_NAME}/
       )

     ke akhir file (tetapi sebelum ``ament_package()``).


3 Menulis file peluncuran
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. tab::

   .. grup-tab :: File peluncuran Python

     Di dalam direktori ``launch`` Anda, buat file peluncuran baru bernama ``my_script_launch.py``.
     ``_launch.py`` direkomendasikan, tetapi tidak wajib, sebagai akhiran file untuk file peluncuran Python.
     Namun, nama file peluncuran harus diakhiri dengan ``launch.py`` agar dikenali dan dilengkapi secara otomatis oleh ``ros2 launch``.

     File peluncuran Anda harus menentukan fungsi ``generate_launch_description()`` yang mengembalikan ``launch.LaunchDescription()`` untuk digunakan oleh kata kerja ``ros2 launch``.

     .. blok kode :: python

       peluncuran impor
       impor launch_ros.actions

       def generate_launch_description():
           kembali launch.LaunchDescription([
               launch_ros.actions.Node(
                   paket='demo_nodes_cpp',
                   dapat dieksekusi='pembicara',
                   nama='pembicara'),
         ])

   .. grup-tab :: File peluncuran XML

     Di dalam direktori ``launch`` Anda, buat file peluncuran baru bernama ``my_script_launch.xml``.
     ``_launch.xml`` direkomendasikan, tetapi tidak wajib, sebagai akhiran file untuk file peluncuran XML.

     .. blok kode :: xml

       <peluncuran>
         <node pkg="demo_nodes_cpp" exec="pembicara" name="pembicara"/>
       </peluncuran>

   .. grup-tab :: file peluncuran YAML

     Di dalam direktori ``launch`` Anda, buat file peluncuran baru bernama ``my_script_launch.yaml``.
     ``_launch.yaml`` direkomendasikan, tetapi tidak wajib, sebagai akhiran file untuk file peluncuran YAML.

     .. blok kode :: yaml

       meluncurkan:

       - simpul:
           pkg: "demo_nodes_cpp"
           exe: "pembicara"
           nama: "pembicara"


4 Membangun dan menjalankan file peluncuran
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Pergi ke tingkat atas ruang kerja, dan bangun:

.. blok kode :: konsol

   membangun colcon

Setelah ``colcon build`` berhasil dan Anda mendapatkan sumber ruang kerja, Anda seharusnya dapatjalankan file peluncuran sebagai berikut:

.. tab::

   .. grup-tab:: Paket Python

     .. tab::

       .. grup-tab :: File peluncuran Python

         .. blok kode :: konsol

           ros2 luncurkan py_launch_example my_script_launch.py

       .. grup-tab :: File peluncuran XML

         .. blok kode :: konsol

           ros2 luncurkan py_launch_example my_script_launch.xml

       .. grup-tab :: file peluncuran YAML

         .. blok kode :: konsol

           ros2 luncurkan py_launch_example my_script_launch.yaml

   .. grup-tab:: Paket C++

     .. tab::

       .. grup-tab :: File peluncuran Python

         .. blok kode :: konsol

           ros2 luncurkan cpp_launch_example my_script_launch.py

       .. grup-tab :: File peluncuran XML

         .. blok kode :: konsol

           ros2 meluncurkan cpp_launch_example my_script_launch.xml

       .. grup-tab :: file peluncuran YAML

         .. blok kode :: konsol

           ros2 meluncurkan cpp_launch_example my_script_launch.yaml


Dokumentasi
-------------

`Dokumentasi peluncuran <https://github.com/ros2/launch/blob/{REPOS_FILE_BRANCH}/launch/doc/source/architecture.rst>`__ memberikan detail lebih lanjut tentang konsep yang juga digunakan dalam ``launch_ros`` .

Dokumentasi tambahan/contoh kemampuan peluncuran akan segera hadir.
Lihat kode sumber (https://github.com/ros2/launch dan https://github.com/ros2/launch_ros) untuk sementara.