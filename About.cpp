// About.cpp
// Emerging Programming Language About Application
// Version 3.0
// Fixed for text display

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

// 全局实例
HINSTANCE hInst;
HWND hMainWnd;
HWND hTabControl;
HWND hEditBox;
HWND hStatusBar;
HWND hListView;
HFONT hTitleFont;
HFONT hNormalFont;
HFONT hMonoFont;
HFONT hBoldFont;
HBRUSH hBgBrush;
HBRUSH hHeaderBrush;
HBRUSH hLinkBrush;
HCURSOR hHandCursor;
HICON hMainIcon;

// 选项卡ID
enum {
    TAB_ABOUT = 0,
    TAB_VERSION,
    TAB_LICENSE,
    TAB_DOCS,
    TAB_EMH,
    TAB_COUNT
};

// EMH文件信息
struct EMHFileInfo {
    std::wstring name;
    std::wstring path;
    std::wstring description;
    std::wstring version;
    std::wstring author;
    std::wstring content;
};

std::vector<EMHFileInfo> g_emhFiles;

// 窗口类名
const wchar_t* CLASS_NAME = L"EmergingAboutClass";
const wchar_t* WINDOW_TITLE = L"关于 Emerging Programming Language v3.0";

// 颜色定义 - 使用更深的颜色确保文字可见
#define COLOR_BG          RGB(255, 255, 255)  // 纯白背景
#define COLOR_HEADER      RGB(240, 240, 255)  // 浅蓝头
#define COLOR_TITLE       RGB(0, 0, 160)      // 深蓝色标题
#define COLOR_TEXT        RGB(0, 0, 0)        // 纯黑色文字
#define COLOR_LINK        RGB(0, 0, 255)      // 蓝色链接
#define COLOR_HOVER       RGB(255, 0, 0)      // 红色悬停
#define COLOR_BORDER      RGB(200, 200, 200)  // 灰色边框
#define COLOR_SELECT      RGB(230, 230, 250)  // 浅紫选中

// 创建内置图标
HICON CreateBuiltInIcon() {
    const int iconSize = 32;
    HDC hdc = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmColor = CreateCompatibleBitmap(hdc, iconSize, iconSize);
    HBITMAP hbmMask = CreateBitmap(iconSize, iconSize, 1, 1, NULL);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmColor);
    
    // 绘制白色背景
    RECT rect = {0, 0, iconSize, iconSize};
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hdcMem, &rect, hBrush);
    DeleteObject(hBrush);
    
    // 绘制蓝色边框
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 102, 204));
    HPEN hOldPen = (HPEN)SelectObject(hdcMem, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcMem, GetStockObject(NULL_BRUSH));
    Rectangle(hdcMem, 2, 2, iconSize-2, iconSize-2);
    
    // 绘制字母"E"
    SetBkMode(hdcMem, TRANSPARENT);
    SetTextColor(hdcMem, RGB(0, 102, 204));
    HFONT hFont = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
    HFONT hOldFont = (HFONT)SelectObject(hdcMem, hFont);
    DrawTextW(hdcMem, L"E", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    SelectObject(hdcMem, hOldFont);
    SelectObject(hdcMem, hOldPen);
    SelectObject(hdcMem, hOldBrush);
    DeleteObject(hFont);
    DeleteObject(hPen);
    
    SelectObject(hdcMem, hbmOld);
    
    ICONINFO ii = {0};
    ii.fIcon = TRUE;
    ii.hbmColor = hbmColor;
    ii.hbmMask = hbmMask;
    HICON hIcon = CreateIconIndirect(&ii);
    
    DeleteObject(hbmColor);
    DeleteObject(hbmMask);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdc);
    
    return hIcon;
}

// 初始化EMH文件内容
void InitializeEMHFiles() {
    // iostream.emh
    g_emhFiles.push_back({
        L"iostream.emh",
        L"using\\iostream.emh",
        L"输入输出流 - out.println, out.print, 彩色输出",
        L"3.0",
        L"Emerging Team",
        L"// iostream.emh - Emerging I/O Stream Library v3.0\n"
        L"// 使用: using \"iostream.emh\"\n\n"
        L"namespace out {\n"
        L"    function print(string str) -> void\n"
        L"    function print(int num) -> void\n"
        L"    function println(string str) -> void\n"
        L"    function println() -> void\n"
        L"    function printf(string format, ...) -> void\n"
        L"    \n"
        L"    function red(string str) -> void\n"
        L"    function green(string str) -> void\n"
        L"    function blue(string str) -> void\n"
        L"    function yellow(string str) -> void\n"
        L"}\n\n"
        L"namespace in {\n"
        L"    function read() -> string\n"
        L"    function readInt() -> int\n"
        L"    function prompt(string msg) -> string\n"
        L"}\n\n"
        L"namespace console {\n"
        L"    function clear() -> void\n"
        L"    function setColor(int fg, int bg) -> void\n"
        L"    function gotoxy(int x, int y) -> void\n"
        L"}"
    });
    
    // system.emh
    g_emhFiles.push_back({
        L"system.emh",
        L"using\\system.emh",
        L"系统调用 - 进程、文件、环境变量、端口操作",
        L"3.0",
        L"Emerging Team",
        L"// system.emh - Emerging System Library v3.0\n"
        L"// 使用: using \"system.emh\"\n\n"
        L"type byte = unsigned char\n"
        L"type word = unsigned short\n"
        L"type dword = unsigned int\n\n"
        L"struct SystemInfo {\n"
        L"    string os_name\n"
        L"    string os_version\n"
        L"    uint32 memory_total\n"
        L"    uint32 memory_free\n"
        L"}\n\n"
        L"function system_info() -> SystemInfo\n"
        L"function system_beep(uint32 freq, uint32 duration) -> void\n"
        L"function system_exec(string program) -> int\n\n"
        L"function inb(uint16 port) -> uint8\n"
        L"function outb(uint16 port, uint8 value) -> void\n"
        L"function inw(uint16 port) -> uint16\n"
        L"function outw(uint16 port, uint16 value) -> void"
    });
    
    // io.emh
    g_emhFiles.push_back({
        L"io.emh",
        L"using\\io.emh",
        L"文件I/O操作 - 文件读写、目录操作",
        L"3.0",
        L"Emerging Team",
        L"// io.emh - Emerging File I/O Library v3.0\n"
        L"// 使用: using \"io.emh\"\n\n"
        L"struct File {\n"
        L"    handle handle\n"
        L"    string path\n"
        L"    uint32 size\n"
        L"}\n\n"
        L"function file_open(string path, uint32 mode) -> File\n"
        L"function file_close(File file) -> void\n"
        L"function file_read(File file, byte[] buffer, uint32 count) -> uint32\n"
        L"function file_write(File file, byte[] buffer, uint32 count) -> uint32\n"
        L"function file_exists(string path) -> bool\n"
        L"function file_delete(string path) -> bool"
    });
    
    // memory.emh
    g_emhFiles.push_back({
        L"memory.emh",
        L"using\\memory.emh",
        L"内存管理 - malloc, free, 内存池",
        L"3.0",
        L"Emerging Team",
        L"// memory.emh - Emerging Memory Management Library v3.0\n"
        L"// 使用: using \"memory.emh\"\n\n"
        L"function malloc(uint32 size) -> ptr\n"
        L"function calloc(uint32 count, uint32 size) -> ptr\n"
        L"function free(ptr p) -> void\n\n"
        L"function memcpy(ptr dest, ptr src, uint32 size) -> ptr\n"
        L"function memset(ptr dest, byte value, uint32 size) -> ptr\n"
        L"function memcmp(ptr p1, ptr p2, uint32 size) -> int\n\n"
        L"struct MemoryPool {\n"
        L"    ptr start\n"
        L"    uint32 size\n"
        L"    uint32 used\n"
        L"}\n"
        L"function pool_create(uint32 size) -> MemoryPool"
    });
    
    // string.emh
    g_emhFiles.push_back({
        L"string.emh",
        L"using\\string.emh",
        L"字符串处理 - 查找、替换、分割、格式化",
        L"3.0",
        L"Emerging Team",
        L"// string.emh - Emerging String Library v3.0\n"
        L"// 使用: using \"string.emh\"\n\n"
        L"function length(string str) -> uint32\n"
        L"function substring(string str, uint32 start, uint32 len) -> string\n"
        L"function replace(string str, string old, string new) -> string\n"
        L"function split(string str, string delim) -> string[]\n"
        L"function toUpper(string str) -> string\n"
        L"function toLower(string str) -> string\n"
        L"function trim(string str) -> string\n"
        L"function format(string fmt, ...) -> string"
    });
    
    // math.emh
    g_emhFiles.push_back({
        L"math.emh",
        L"using\\math.emh",
        L"数学函数 - 三角函数、指数、对数、随机数",
        L"3.0",
        L"Emerging Team",
        L"// math.emh - Emerging Mathematics Library v3.0\n"
        L"// 使用: using \"math.emh\"\n\n"
        L"const PI = 3.141592653589793\n"
        L"const E = 2.718281828459045\n\n"
        L"function sin(float angle) -> float\n"
        L"function cos(float angle) -> float\n"
        L"function tan(float angle) -> float\n"
        L"function sqrt(float x) -> float\n"
        L"function pow(float x, float y) -> float\n"
        L"function log(float x) -> float\n"
        L"function random() -> float\n"
        L"function random(int max) -> int"
    });
    
    // graphics.emh
    g_emhFiles.push_back({
        L"graphics.emh",
        L"using\\graphics.emh",
        L"图形绘制 - 像素、线条、矩形、圆形",
        L"3.0",
        L"Emerging Team",
        L"// graphics.emh - Emerging Graphics Library v3.0\n"
        L"// 使用: using \"graphics.emh\"\n\n"
        L"const BLACK = 0\n"
        L"const WHITE = 15\n\n"
        L"function initGraphics(int width, int height) -> void\n"
        L"function drawPixel(int x, int y, int color) -> void\n"
        L"function drawLine(int x1, int y1, int x2, int y2, int color) -> void\n"
        L"function drawRect(int x, int y, int w, int h, int color) -> void\n"
        L"function fillRect(int x, int y, int w, int h, int color) -> void\n"
        L"function drawCircle(int x, int y, int r, int color) -> void"
    });
}

// 函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitializeFonts(void);
void CleanupFonts(void);
void CreateTabControls(HWND hwnd);
void ShowTabContent(int tabIndex);
void DisplayEMHContent(HWND hwnd, const std::wstring& filename);
void DrawAboutContent(HDC hdc, RECT* rect);
void DrawVersionContent(HDC hdc, RECT* rect);
void DrawLicenseContent(HDC hdc, RECT* rect);
void DrawDocsContent(HDC hdc, RECT* rect);
void DrawEMHList(HDC hdc, RECT* rect);
void DrawWatermark(HDC hdc, RECT* rect);
void OpenLink(const wchar_t* url);

// 初始化字体
void InitializeFonts(void) {
    hTitleFont = CreateFontW(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
    
    hBoldFont = CreateFontW(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
    
    hNormalFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
    
    hMonoFont = CreateFontW(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas");
    
    hBgBrush = CreateSolidBrush(COLOR_BG);
    hHeaderBrush = CreateSolidBrush(COLOR_HEADER);
    hLinkBrush = CreateSolidBrush(COLOR_LINK);
    hHandCursor = LoadCursor(NULL, IDC_HAND);
    
    hMainIcon = CreateBuiltInIcon();
}

// 清理字体
void CleanupFonts(void) {
    if (hTitleFont) DeleteObject(hTitleFont);
    if (hBoldFont) DeleteObject(hBoldFont);
    if (hNormalFont) DeleteObject(hNormalFont);
    if (hMonoFont) DeleteObject(hMonoFont);
    if (hBgBrush) DeleteObject(hBgBrush);
    if (hHeaderBrush) DeleteObject(hHeaderBrush);
    if (hLinkBrush) DeleteObject(hLinkBrush);
    if (hMainIcon) DestroyIcon(hMainIcon);
}

// 创建选项卡控件
void CreateTabControls(HWND hwnd) {
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_TAB_CLASSES | ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);
    
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);
    
    // 创建选项卡
    hTabControl = CreateWindowW(WC_TABCONTROL, NULL, 
                                WS_CHILD | WS_VISIBLE | TCS_FIXEDWIDTH,
                                0, 0, rcClient.right, rcClient.bottom,
                                hwnd, NULL, hInst, NULL);
    
    // 设置选项卡字体
    SendMessage(hTabControl, WM_SETFONT, (WPARAM)hNormalFont, TRUE);
    
    // 添加选项卡
    TCITEMW tie;
    tie.mask = TCIF_TEXT;
    
    const wchar_t* tabNames[] = {L"关于", L"版本", L"许可证", L"文档", L"EMH文件"};
    
    for (int i = 0; i < TAB_COUNT; i++) {
        tie.pszText = (LPWSTR)tabNames[i];
        TabCtrl_InsertItem(hTabControl, i, &tie);
    }
    
    // 创建编辑框用于显示EMH内容
    hEditBox = CreateWindowW(L"EDIT", NULL, 
                            WS_CHILD | WS_BORDER | ES_MULTILINE | 
                            ES_AUTOVSCROLL | ES_READONLY | WS_VSCROLL | 
                            ES_NOHIDESEL,
                            0, 0, 0, 0, hTabControl, NULL, hInst, NULL);
    
    SendMessage(hEditBox, WM_SETFONT, (WPARAM)hMonoFont, TRUE);
    
    // 创建列表视图用于EMH文件列表
    hListView = CreateWindowW(WC_LISTVIEW, NULL,
                             WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
                             0, 0, 0, 0, hTabControl, NULL, hInst, NULL);
    
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    
    // 添加列
    LVCOLUMNW lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    
    lvc.pszText = (LPWSTR)L"文件名";
    lvc.cx = 150;
    ListView_InsertColumn(hListView, 0, &lvc);
    
    lvc.pszText = (LPWSTR)L"版本";
    lvc.cx = 80;
    ListView_InsertColumn(hListView, 1, &lvc);
    
    lvc.pszText = (LPWSTR)L"描述";
    lvc.cx = 350;
    ListView_InsertColumn(hListView, 2, &lvc);
    
    // 添加EMH文件到列表
    for (size_t i = 0; i < g_emhFiles.size(); i++) {
        LVITEMW lvi = {0};
        lvi.mask = LVIF_TEXT;
        lvi.iItem = (int)i;
        
        lvi.iSubItem = 0;
        lvi.pszText = (LPWSTR)g_emhFiles[i].name.c_str();
        ListView_InsertItem(hListView, &lvi);
        
        ListView_SetItemText(hListView, i, 1, (LPWSTR)g_emhFiles[i].version.c_str());
        ListView_SetItemText(hListView, i, 2, (LPWSTR)g_emhFiles[i].description.c_str());
    }
    
    // 创建状态栏
    hStatusBar = CreateWindowW(STATUSCLASSNAME, NULL,
                              WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
                              0, 0, 0, 0, hwnd, NULL, hInst, NULL);
    
    // 显示第一个选项卡
    ShowTabContent(TAB_ABOUT);
}

// 显示选项卡内容
void ShowTabContent(int tabIndex) {
    RECT rc;
    GetClientRect(hTabControl, &rc);
    TabCtrl_AdjustRect(hTabControl, FALSE, &rc);
    
    // 隐藏所有子窗口
    ShowWindow(hEditBox, SW_HIDE);
    ShowWindow(hListView, SW_HIDE);
    
    // 根据选项卡显示不同内容
    switch (tabIndex) {
        case TAB_ABOUT:
        case TAB_VERSION:
        case TAB_LICENSE:
        case TAB_DOCS:
            // 这些选项卡通过WM_PAINT绘制
            InvalidateRect(hTabControl, NULL, TRUE);
            break;
            
        case TAB_EMH:
            // 显示列表视图
            SetWindowPos(hListView, NULL,
                        rc.left, rc.top,
                        rc.right - rc.left,
                        rc.bottom - rc.top,
                        SWP_NOZORDER);
            ShowWindow(hListView, SW_SHOW);
            InvalidateRect(hListView, NULL, TRUE);
            break;
    }
    
    // 更新状态栏
    const wchar_t* statusText[] = {
        L"Emerging Programming Language v3.0 - 关于信息 | .emh 头文件格式",
        L"Emerging Programming Language v3.0 - 版本信息 | 支持x86/x64/ARM",
        L"Emerging Programming Language v3.0 - MIT许可证 | 开源免费",
        L"Emerging Programming Language v3.0 - 快速入门文档 | 使用.emh头文件",
        L"Emerging Programming Language v3.0 - EMH头文件列表 | 双击查看内容"
    };
    
    SendMessageW(hStatusBar, SB_SETTEXTW, 0, (LPARAM)statusText[tabIndex]);
}

// 显示EMH文件内容
void DisplayEMHContent(HWND hwnd, const std::wstring& filename) {
    // 查找文件内容
    std::wstring content = L"// 文件未找到";
    for (const auto& file : g_emhFiles) {
        if (file.name == filename) {
            content = file.content;
            break;
        }
    }
    
    // 设置编辑框内容
    SetWindowTextW(hEditBox, content.c_str());
    
    // 显示编辑框
    RECT rc;
    GetClientRect(hTabControl, &rc);
    TabCtrl_AdjustRect(hTabControl, FALSE, &rc);
    
    SetWindowPos(hEditBox, NULL,
                rc.left, rc.top,
                rc.right - rc.left,
                rc.bottom - rc.top,
                SWP_NOZORDER);
    
    ShowWindow(hListView, SW_HIDE);
    ShowWindow(hEditBox, SW_SHOW);
}

// 绘制关于内容
void DrawAboutContent(HDC hdc, RECT* rect) {
    // 填充白色背景
    FillRect(hdc, rect, hBgBrush);
    
    HFONT hOldFont = (HFONT)SelectObject(hdc, hTitleFont);
    SetTextColor(hdc, COLOR_TITLE);
    SetBkMode(hdc, TRANSPARENT);
    
    // 标题
    TextOutW(hdc, 30, 30, L"Emerging Programming Language", 29);
    
    // 副标题
    SelectObject(hdc, hBoldFont);
    SetTextColor(hdc, RGB(0, 0, 150));
    TextOutW(hdc, 30, 70, L"Version 3.0 - 操作系统开发语言", 26);
    
    // 描述 - 使用纯黑色
    SelectObject(hdc, hNormalFont);
    SetTextColor(hdc, RGB(0, 0, 0));
    
    const wchar_t* desc[] = {
        L"Emerging是一种专门为操作系统开发设计的高级编程语言，",
        L"它结合了高级语言的易用性和底层硬件访问能力。",
        L"",
        L"主要特性：",
        L"? 直接硬件访问 - inb/outb 端口操作",
        L"? 内存管理 - malloc/free 内存分配",
        L"? 多任务支持 - 进程和线程管理",
        L"? 中断处理 - cli/sti 中断控制",
        L"? 文件系统 - 文件和目录操作",
        L"? EMH头文件 - 使用 .emh 格式",
        L"",
        L"out 命名空间增强：",
        L"  out.print()    - 输出不换行",
        L"  out.println()  - 输出并换行",
        L"  out.red()      - 红色输出",
        L"  out.green()    - 绿色输出",
        L"  out.blue()     - 蓝色输出"
    };
    
    int y = 110;
    for (int i = 0; i < sizeof(desc)/sizeof(desc[0]); i++) {
        TextOutW(hdc, 30, y, desc[i], (int)wcslen(desc[i]));
        y += (i < 3) ? 25 : 22;
    }
    
    // 底部链接 - 蓝色
    SetTextColor(hdc, RGB(0, 0, 255));
    
    const wchar_t* links[] = {L"官方网站", L"GitHub", L"文档", L"社区"};
    int linkX[] = {30, 150, 270, 390};
    
    for (int i = 0; i < 4; i++) {
        TextOutW(hdc, linkX[i], 380, links[i], (int)wcslen(links[i]));
    }
    
    // 版权信息 - 灰色
    SetTextColor(hdc, RGB(100, 100, 100));
    TextOutW(hdc, 30, 420, L"? 2024 Emerging Language Team. All rights reserved.", 53);
    
    SelectObject(hdc, hOldFont);
    DrawWatermark(hdc, rect);
}

// 绘制版本内容
void DrawVersionContent(HDC hdc, RECT* rect) {
    // 填充白色背景
    FillRect(hdc, rect, hBgBrush);
    
    HFONT hOldFont = (HFONT)SelectObject(hdc, hTitleFont);
    SetTextColor(hdc, COLOR_TITLE);
    SetBkMode(hdc, TRANSPARENT);
    
    TextOutW(hdc, 30, 30, L"版本信息", 8);
    
    SelectObject(hdc, hMonoFont);
    SetTextColor(hdc, RGB(0, 0, 0));  // 纯黑色
    
    const wchar_t* versionInfo[] = {
        L"Emerging Programming Language v3.0.0",
        L"====================================",
        L"",
        L"核心组件:",
        L"  编译器前端:    3.0.0.2024",
        L"  代码生成器:    3.0.0.2024",
        L"  链接器:        3.0.0.2024",
        L"  运行时库:      3.0.0.2024",
        L"  调试器:        3.0.0.2024",
        L"",
        L"EMH头文件版本:",
        L"  iostream.emh:  3.0",
        L"  system.emh:     3.0",
        L"  io.emh:         3.0",
        L"  memory.emh:     3.0",
        L"  string.emh:     3.0",
        L"  math.emh:       3.0",
        L"  graphics.emh:   3.0",
        L"",
        L"构建信息:",
        L"  构建日期:      2024-01-15",
        L"  平台:          x86/x64/ARM",
        L"  优化级别:      O2",
        L"  Unicode:       UTF-8/UTF-16",
        L"",
        L"系统要求:",
        L"  Windows 10/11 或更高版本",
        L"  Visual C++ 运行时 14.0+",
        L"  内存: 最低 64MB",
        L"  磁盘空间: 100MB"
    };
    
    int y = 70;
    for (int i = 0; i < sizeof(versionInfo)/sizeof(versionInfo[0]); i++) {
        TextOutW(hdc, 30, y, versionInfo[i], (int)wcslen(versionInfo[i]));
        y += 20;
    }
    
    SelectObject(hdc, hOldFont);
}

// 绘制许可证内容
void DrawLicenseContent(HDC hdc, RECT* rect) {
    // 填充白色背景
    FillRect(hdc, rect, hBgBrush);
    
    HFONT hOldFont = (HFONT)SelectObject(hdc, hTitleFont);
    SetTextColor(hdc, COLOR_TITLE);
    SetBkMode(hdc, TRANSPARENT);
    
    TextOutW(hdc, 30, 30, L"MIT 许可证", 9);
    
    SelectObject(hdc, hMonoFont);
    SetTextColor(hdc, RGB(0, 0, 0));  // 纯黑色
    
    const wchar_t* license = 
        L"MIT License\r\n\r\n"
        L"Copyright (c) 2024 Emerging Programming Language\r\n\r\n"
        L"Permission is hereby granted, free of charge, to any person obtaining a copy\r\n"
        L"of this software and associated documentation files (the \"Software\"), to deal\r\n"
        L"in the Software without restriction, including without limitation the rights\r\n"
        L"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\r\n"
        L"copies of the Software, and to permit persons to whom the Software is\r\n"
        L"furnished to do so, subject to the following conditions:\r\n\r\n"
        L"The above copyright notice and this permission notice shall be included in all\r\n"
        L"copies or substantial portions of the Software.\r\n\r\n"
        L"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\r\n"
        L"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\r\n"
        L"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\r\n"
        L"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\r\n"
        L"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\r\n"
        L"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\r\n"
        L"SOFTWARE.";
    
    RECT textRect = {30, 70, rect->right - 30, rect->bottom - 30};
    DrawTextW(hdc, license, -1, &textRect, DT_LEFT | DT_TOP | DT_WORDBREAK);
    
    SelectObject(hdc, hOldFont);
}

// 绘制文档内容
void DrawDocsContent(HDC hdc, RECT* rect) {
    // 填充白色背景
    FillRect(hdc, rect, hBgBrush);
    
    HFONT hOldFont = (HFONT)SelectObject(hdc, hTitleFont);
    SetTextColor(hdc, COLOR_TITLE);
    SetBkMode(hdc, TRANSPARENT);
    
    TextOutW(hdc, 30, 30, L"快速入门 - 使用 .emh 头文件", 24);
    
    SelectObject(hdc, hNormalFont);
    SetTextColor(hdc, RGB(0, 0, 0));  // 纯黑色
    
    const wchar_t* docs[] = {
        L"1. 导入头文件:",
        L"   using \"iostream.emh\"",
        L"   using \"system.emh\"",
        L"   using \"memory.emh\"",
        L"",
        L"2. 输出示例:",
        L"   out.print(\"Hello\");           // 不换行输出",
        L"   out.println(\"World\");          // 输出并换行",
        L"   out.printf(\"Value: %d\", 42);   // 格式化输出",
        L"   out.red(\"错误信息\");            // 红色输出",
        L"   out.green(\"成功\");              // 绿色输出",
        L"   out.blue(\"提示\");               // 蓝色输出",
        L"",
        L"3. 输入示例:",
        L"   string name = in.prompt(\"姓名: \");",
        L"   int age = in.promptInt(\"年龄: \");",
        L"   char ch = in.readChar();",
        L"",
        L"4. 控制台控制:",
        L"   console.clear();",
        L"   console.setColor(WHITE, BLUE);",
        L"   console.gotoxy(10, 10);",
        L"",
        L"5. 系统调用:",
        L"   SystemInfo info = system_info();",
        L"   out.println(info.os_name);",
        L"   system_beep(1000, 500);",
        L"",
        L"6. 内存管理:",
        L"   ptr p = malloc(1024);",
        L"   memset(p, 0, 1024);",
        L"   free(p);",
        L"",
        L"7. 编译命令:",
        L"   emerging --run program.emg",
        L"   emerging --emergingcompiler program.emg -out program.exe"
    };
    
    int y = 70;
    for (int i = 0; i < sizeof(docs)/sizeof(docs[0]); i++) {
        TextOutW(hdc, 30, y, docs[i], (int)wcslen(docs[i]));
        y += ((int)wcslen(docs[i]) > 30) ? 22 : 25;
    }
    
    SelectObject(hdc, hOldFont);
}

// 绘制EMH文件列表
void DrawEMHList(HDC hdc, RECT* rect) {
    // 填充白色背景
    FillRect(hdc, rect, hBgBrush);
    
    HFONT hOldFont = (HFONT)SelectObject(hdc, hBoldFont);
    SetTextColor(hdc, COLOR_TITLE);
    SetBkMode(hdc, TRANSPARENT);
    
    TextOutW(hdc, 30, 30, L"EMH 头文件列表", 14);
    
    SelectObject(hdc, hNormalFont);
    
    int y = 70;
    for (size_t i = 0; i < g_emhFiles.size(); i++) {
        // 绘制背景
        if (i % 2 == 0) {
            RECT bgRect = {25, y - 2, rect->right - 25, y + 22};
            FillRect(hdc, &bgRect, hHeaderBrush);
        }
        
        // 文件名 - 蓝色
        SetTextColor(hdc, RGB(0, 0, 255));
        TextOutW(hdc, 30, y, g_emhFiles[i].name.c_str(), (int)g_emhFiles[i].name.length());
        
        // 版本 - 深绿色
        SetTextColor(hdc, RGB(0, 100, 0));
        TextOutW(hdc, 160, y, g_emhFiles[i].version.c_str(), (int)g_emhFiles[i].version.length());
        
        // 描述 - 黑色
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutW(hdc, 250, y, g_emhFiles[i].description.c_str(), (int)g_emhFiles[i].description.length());
        
        y += 25;
    }
    
    // 使用说明
    y += 10;
    SetTextColor(hdc, RGB(100, 100, 100));
    TextOutW(hdc, 30, y, L"使用方式: using \"filename.emh\"", 30);
    y += 25;
    TextOutW(hdc, 30, y, L"示例: using \"iostream.emh\"", 26);
    y += 25;
    TextOutW(hdc, 30, y, L"      using \"system.emh\"", 24);
    y += 25;
    TextOutW(hdc, 30, y, L"      using \"memory.emh\"", 24);
    
    SelectObject(hdc, hOldFont);
}

// 绘制水印
void DrawWatermark(HDC hdc, RECT* rect) {
    HFONT hWatermarkFont = CreateFontW(48, 0, 0, 0, FW_BOLD, 
                                       FALSE, FALSE, FALSE,
                                       DEFAULT_CHARSET, 
                                       OUT_DEFAULT_PRECIS, 
                                       CLIP_DEFAULT_PRECIS,
                                       CLEARTYPE_QUALITY, 
                                       DEFAULT_PITCH | FF_DONTCARE, 
                                       L"Segoe UI");
    
    HFONT hOldFont = (HFONT)SelectObject(hdc, hWatermarkFont);
    SetTextColor(hdc, RGB(220, 220, 220));  // 浅灰色水印
    SetBkMode(hdc, TRANSPARENT);
    
    const wchar_t* watermark = L".emh";
    SIZE size;
    GetTextExtentPoint32W(hdc, watermark, (int)wcslen(watermark), &size);
    
    int x = rect->right - size.cx - 50;
    int y = rect->bottom - size.cy - 50;
    
    TextOutW(hdc, x, y, watermark, (int)wcslen(watermark));
    
    SelectObject(hdc, hOldFont);
    DeleteObject(hWatermarkFont);
}

// 打开链接
void OpenLink(const wchar_t* url) {
    ShellExecuteW(NULL, L"open", url, NULL, NULL, SW_SHOW);
}

// 窗口过程
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            InitializeFonts();
            InitializeEMHFiles();
            CreateTabControls(hwnd);
            return 0;
            
        case WM_SIZE:
            {
                RECT rc;
                GetClientRect(hwnd, &rc);
                
                // 调整状态栏
                SendMessage(hStatusBar, WM_SIZE, 0, 0);
                
                // 获取状态栏高度
                RECT rcStatus;
                GetWindowRect(hStatusBar, &rcStatus);
                int statusHeight = rcStatus.bottom - rcStatus.top;
                
                // 调整选项卡控件
                SetWindowPos(hTabControl, NULL, 
                            0, 0, rc.right, rc.bottom - statusHeight,
                            SWP_NOZORDER);
            }
            return 0;
            
        case WM_NOTIFY:
            {
                NMHDR* pnmh = (NMHDR*)lParam;
                if (pnmh->hwndFrom == hTabControl) {
                    switch (pnmh->code) {
                        case TCN_SELCHANGE:
                            int tabIndex = TabCtrl_GetCurSel(hTabControl);
                            ShowTabContent(tabIndex);
                            return 0;
                    }
                }
                else if (pnmh->hwndFrom == hListView) {
                    switch (pnmh->code) {
                        case NM_DBLCLK:
                            {
                                int index = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
                                if (index >= 0) {
                                    wchar_t filename[256];
                                    ListView_GetItemText(hListView, index, 0, filename, 256);
                                    DisplayEMHContent(hwnd, filename);
                                }
                            }
                            return 0;
                    }
                }
            }
            return 0;
            
        case WM_ERASEBKGND:
            return 1;  // 防止闪烁
            
        case WM_DESTROY:
            CleanupFonts();
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// 程序入口
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;
    
    // 注册窗口类
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(COLOR_BG);  // 直接使用白色背景
    wc.lpszClassName = CLASS_NAME;
    
    RegisterClassExW(&wc);
    
    // 计算窗口大小
    int windowWidth = 800;
    int windowHeight = 650;
    
    RECT rc = {0, 0, windowWidth, windowHeight};
    AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_CLIENTEDGE);
    
    // 创建窗口
    hMainWnd = CreateWindowExW(WS_EX_CLIENTEDGE, CLASS_NAME, WINDOW_TITLE,
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT, 
                              rc.right - rc.left, rc.bottom - rc.top,
                              NULL, NULL, hInstance, NULL);
    
    if (!hMainWnd) {
        return 1;
    }
    
    // 设置窗口图标
    hMainIcon = CreateBuiltInIcon();
    if (hMainIcon) {
        SendMessage(hMainWnd, WM_SETICON, ICON_BIG, (LPARAM)hMainIcon);
        SendMessage(hMainWnd, WM_SETICON, ICON_SMALL, (LPARAM)hMainIcon);
    }
    
    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);
    
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}
