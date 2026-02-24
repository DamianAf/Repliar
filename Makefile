TARGET = Repliar

.SILENT:
all:
	ninja -C build
	./bin/$(TARGET)

cmake:
	cmake -B build -G "Ninja" -DPROJ_NAME=$(TARGET) -DCMAKE_BUILD_TYPE=Debug.

cmakeRelease:
	cmake -B build -G "Ninja" -DPROJ_NAME=$(TARGET) -DCMAKE_BUILD_TYPE=Release .
