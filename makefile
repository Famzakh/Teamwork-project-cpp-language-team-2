CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp Utils.cpp Transaction.cpp Asset.cpp FinanceManager.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = SmartFinanceTracker.exe

# Khi gõ 'make', nó sẽ thực hiện cạả 2 việc: build (biên dịch) và run (chy)
all: build run

build: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Lệnh tự động chạy chương trình trên Windows
run:
	.\$(EXEC)

clean:
	del *.o $(EXEC)