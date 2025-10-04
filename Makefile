TARGET = Repliar

.SILENT:
all:
	ninja -C build
	./bin/$(TARGET).exe