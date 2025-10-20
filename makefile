# Hospital System Makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -O2
TARGET = hospital_system
SOURCES = main.cpp hospitalsystem.cpp
HEADERS = hospitalsystem.h patient.h priorityqueue.h circularqueue.h \
          array.h list.h stack.h queue.h

$(TARGET): $(SOURCES) $(HEADERS)
	@echo "🏥 Compiling Hospital Management System..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)
	@echo "✅ Compilation successful! Run with: ./$(TARGET)"

run: $(TARGET)
	@echo "🚀 Starting Hospital System..."
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
	@echo "🧹 Cleanup completed"

debug: $(TARGET)
	gdb ./$(TARGET)

.PHONY: run clean debug
