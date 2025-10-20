# Hospital Management System Makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -O2
TARGET = build/hospital_system
SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/hospitalsystem.cpp
HEADERS = $(SRCDIR)/hospitalsystem.h $(SRCDIR)/patient.h \
          $(SRCDIR)/priorityqueue.h $(SRCDIR)/circularqueue.h \
          $(SRCDIR)/array.h $(SRCDIR)/list.h $(SRCDIR)/stack.h

# Create build directory if it doesn't exist
$(shell mkdir -p build)

$(TARGET): $(SOURCES) $(HEADERS)
	@echo "🏥 Compiling Hospital Management System..."
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -o $(TARGET) $(SOURCES)
	@echo "✅ Compilation successful! Run with: ./$(TARGET)"

run: $(TARGET)
	@echo "🚀 Starting Hospital System..."
	./$(TARGET)

clean:
	rm -rf build
	@echo "🧹 Build directory cleaned"

debug: $(TARGET)
	@gdb ./$(TARGET)

.PHONY: run clean debug
