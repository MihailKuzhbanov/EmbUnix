sudo apt-get install build-essential bison flex autoconf
sudo apt-get install python-wxgtk3.0 pyro mercurial
sudo apt-get install python-nevow python-matplotlib python-lxml python-zeroconf python-cycler
sudo apt-get install python-autobahn python-u-msgpack
mkdir ~/Beremiz
cd ~/Beremiz
hg clone https://bitbucket.org/automforge/beremiz
hg clone https://bitbucket.org/automforge/matiec
cd ~/Beremiz/matiec
autoreconf -i
./configure
make
sudo apt-get install pip
pip install future
cd ~/Beremiz/beremiz
python Beremiz.py
