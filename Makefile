

all: jni/*
	ndk-build	

install: all
	install -d ipk/data/opt/etc/preload.d/
	install libs/armeabi-v7a/lib*.so ipk/data/opt/etc/preload.d/

ipk: all
	$(MAKE) -C ipk clean
	$(MAKE) install
	$(MAKE) -C ipk
	mv ipk/*.ipk ./

clean:
	$(MAKE) -C ipk clean
	rm -f *.ipk
	rm -rf libs
	rm -rf obj
	rm ipk/data/opt/etc/preload.d/libboost_bitrate.so
    