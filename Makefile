TARGET = Repliar

.SILENT:
all:
	ninja -C build
	./bin/$(TARGET)
cmake:
	cmake -B build -G "Ninja" -DPROJ_NAME=$(TARGET) .