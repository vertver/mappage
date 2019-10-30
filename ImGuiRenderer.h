#pragma once
#include <QOpenGLExtraFunctions>
#include <QObject>
#include <QPoint>
#include <imgui.h>
#include <memory>
#include <QQuickWindow>
#include <QQuickView>
#include <QQuickItem>
#include <QClipboard>
#include <QDateTime>
#include <QApplication>
#include <QTimer>
#include <QSurfaceFormat>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

/*
	TODO: place your debug function here
*/
#define REDEBUGOUTPUT(x) OutputDebugStringA(x)

typedef unsigned long long qword_t;
typedef unsigned long dword_t;
typedef unsigned short word_t;
typedef unsigned char byte_t;

struct VulkanSupportStruct {
	dword_t isSupported;
	dword_t MaxVersion;
	dword_t ExtensionsCount;
	dword_t LayersCount;
};

struct OpenGLSupportStruct {
	dword_t isSupported;
	dword_t MaxVersion;
};

class CRenderSupporter
{
private:
	int extsVk = 0;
	int extsGl = 0;
	char** ppVkExtensions = nullptr;
	char** ppGLExtensions = nullptr;
	VulkanSupportStruct VulkanStruct = {};
	OpenGLSupportStruct OpenGLStruct = {};

public:
	CRenderSupporter();
	~CRenderSupporter();

	void GetVulkanStruct(VulkanSupportStruct& Struct);
	void GetOpenGLStruct(OpenGLSupportStruct& Struct);

	char* GetVulkanExtensionName(dword_t id);
	char* GetOpenGLExtensionName(dword_t id);

	bool IsVulkanSupported();
	bool IsOpenGLSupported();
};

class CQtImGuiRender : public QObject, protected QOpenGLExtraFunctions
{
	Q_OBJECT

private:
	double g_Time = 0.0f;
	bool g_MousePressed[3] = { false, false, false };
	float g_MouseWheel;
	float g_MouseWheelH;
	GLuint g_FontTexture = 0;
	int g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
	int g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
	int g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
	unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

public:
	QHash<int, ImGuiKey> keyMap = {
		{ Qt::Key_Tab, ImGuiKey_Tab },
		{ Qt::Key_Left, ImGuiKey_LeftArrow },
		{ Qt::Key_Right, ImGuiKey_RightArrow },
		{ Qt::Key_Up, ImGuiKey_UpArrow },
		{ Qt::Key_Down, ImGuiKey_DownArrow },
		{ Qt::Key_PageUp, ImGuiKey_PageUp },
		{ Qt::Key_PageDown, ImGuiKey_PageDown },
		{ Qt::Key_Home, ImGuiKey_Home },
		{ Qt::Key_End, ImGuiKey_End },
		{ Qt::Key_Delete, ImGuiKey_Delete },
		{ Qt::Key_Backspace, ImGuiKey_Backspace },
		{ Qt::Key_Enter, ImGuiKey_Enter },
		{ Qt::Key_Escape, ImGuiKey_Escape },
		{ Qt::Key_A, ImGuiKey_A },
		{ Qt::Key_C, ImGuiKey_C },
		{ Qt::Key_V, ImGuiKey_V },
		{ Qt::Key_X, ImGuiKey_X },
		{ Qt::Key_Y, ImGuiKey_Y },
		{ Qt::Key_Z, ImGuiKey_Z },
	};

	QByteArray g_currentClipboardText;

	CQtImGuiRender();
	virtual ~CQtImGuiRender();

	static CQtImGuiRender* instance();

	void setT(qreal t) { m_t = t; }
	void setViewportSize(const QSize& size) { m_viewportSize = size; }
	void setWindow(QQuickWindow* window) { m_window = window; }

	bool eventFilter(QObject* watched, QEvent* event);
	void newFrame();
	
public slots:
	void paint();
	
private:
	void onMousePressedChange(QMouseEvent* event);
	void onWheel(QWheelEvent* event);
	void onKeyPressRelease(QKeyEvent* event);

	void renderDrawList(ImDrawData* draw_data);
	bool createFontsTexture();
	bool createDeviceObjects();

	bool initialize();

	QSize m_viewportSize;
	qreal m_t;
	QQuickWindow* m_window;
};


class CQtImGui : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
	CQtImGui();

	qreal t() const;
	void setT(qreal t);

signals:
	void tChanged();

public slots:
	void sync();
	void cleanup();

private slots:
	void handleWindowChanged(QQuickWindow* win);

private:
	qreal m_t;
	CQtImGuiRender* pRender = nullptr;
};

#include <QAbstractListModel>

// в этой программе класс не используется как модель;
// стандартные методы модели оставлены, вырезать и перенаследоваться некогда
class PolylineModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum {
		PathRole = Qt::UserRole + 1,
	};

	explicit PolylineModel(QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

	Q_INVOKABLE int tracksSize() const;
	Q_INVOKABLE QVariant trackData(int idx) const;

private:
	QVector<QVariantList> data_;
};

#include <iostream>

namespace sdl {

	void print_timestamp();

	template<typename T>
	static void trace_delim(T&& value) {
		std::cout << value << std::endl;
	}
	template<typename T, typename... Ts>
	static void trace_delim(T&& value, Ts&&... params) {
		std::cout << value << '|';
		trace_delim(std::forward<Ts>(params)...);
	}
	template<typename T, typename... Ts>
	static void trace_delim_with_timestamp(T&& value, Ts&&... params) {
		print_timestamp();
		trace_delim(std::forward<T>(value), std::forward<Ts>(params)...);
	}

}

#include <vector>

class ImGuiLines : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE void DrawLine(qreal x, qreal y);
	Q_INVOKABLE void Clear();
};

#define SDL_TRACE_ARGS_IMPL(...)	sdl::trace_delim_with_timestamp(__VA_ARGS__)
#define SDL_TRACE_ARGS(...)			SDL_TRACE_ARGS_IMPL(__FUNCTION__, __VA_ARGS__)
