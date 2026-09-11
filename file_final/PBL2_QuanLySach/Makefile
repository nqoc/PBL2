# =====================================================================
#  Makefile - Chuong trinh QUAN LY SACH TRONG CUA HANG (PBL2, ban console)
#
#  Cach dung:
#     make            bien dich toan bo
#     make run        bien dich roi chay
#     make clean      xoa file .o va file chay
#     make rebuild    dich lai tu dau
# =====================================================================

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
TARGET   = QuanLySach

SRCDIR   = src
OBJDIR   = build

SRCS = $(SRCDIR)/TienIch.cpp        \
       $(SRCDIR)/Nguoi.cpp          \
       $(SRCDIR)/KhachHang.cpp      \
       $(SRCDIR)/NhaCungCap.cpp     \
       $(SRCDIR)/TaiKhoan.cpp       \
       $(SRCDIR)/DanhMuc.cpp        \
       $(SRCDIR)/Sach.cpp           \
       $(SRCDIR)/SachGiaoKhoa.cpp   \
       $(SRCDIR)/SachVanHoc.cpp     \
       $(SRCDIR)/SachThieuNhi.cpp   \
       $(SRCDIR)/ChungTu.cpp        \
       $(SRCDIR)/HoaDon.cpp         \
       $(SRCDIR)/PhieuNhap.cpp      \
       $(SRCDIR)/QuanLySach.cpp     \
       $(SRCDIR)/CuaHang.cpp        \
       $(SRCDIR)/ThongKe.cpp        \
       $(SRCDIR)/UngDung.cpp        \
       $(SRCDIR)/UngDung_Sach.cpp   \
       $(SRCDIR)/UngDung_DanhMuc.cpp\
       $(SRCDIR)/UngDung_DoiTac.cpp \
       $(SRCDIR)/UngDung_GiaoDich.cpp \
       $(SRCDIR)/UngDung_ThongKe.cpp \
       $(SRCDIR)/main.cpp

OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo "=== Bien dich xong: $(TARGET) ==="

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TARGET).exe

rebuild: clean all

.PHONY: all run clean rebuild
