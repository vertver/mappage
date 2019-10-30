#include <ImGuiRenderer.h>
#include <imgui.h>
#include <QScreen>
#include <QQmlApplicationEngine>
#include <QQmlContext>


int main(int argc, char *argv[])
{
	ImGuiLines* pLines = new ImGuiLines;

	CRenderSupporter supporter;
	if (supporter.IsVulkanSupported()) {
		/*QVulkanInstance inst;
		inst.setLayers(QByteArrayList() << "VK_LAYER_GOOGLE_threading" << "VK_LAYER_LUNARG_parameter_validation"
			<< "VK_LAYER_LUNARG_object_tracker" << "VK_LAYER_LUNARG_core_validation" << "VK_LAYER_LUNARG_image"
			<< "VK_LAYER_LUNARG_swapchain" << "VK_LAYER_GOOGLE_unique_objects");
			
			QQuickWindow::setSceneGraphBackend(QSGRendererInterface::VulkanRhi);
			qmlRegisterType<CQtImGuiVulkan>("VulkanUnderQML", 1, 0, "CQtImGui");
		*/
	} else {
		if (!supporter.IsOpenGLSupported()) {
			return -1;
		}

		// Use OpenGL 3 Core Profile
		QSurfaceFormat glFormat;
		glFormat.setVersion(3, 3);
		glFormat.setProfile(QSurfaceFormat::CoreProfile);
		QSurfaceFormat::setDefaultFormat(glFormat);
		qmlRegisterType<CQtImGui>("OpenGLUnderQML", 1, 0, "CQtImGui");
	}

	QGuiApplication app(argc, argv);

	auto screens = QGuiApplication::screens();
	SDL_TRACE_ARGS("N of screens", screens.size());

	for (int i = 0, sz = screens.size(); i < sz; ++i) {
		auto screen = screens[i];
		auto rect = screen->geometry();
		SDL_TRACE_ARGS("screen", i, "size", rect.width(), rect.height());
	}

	qmlRegisterType<PolylineModel>("Polyline", 1, 0, "PolylineModel");

	QQuickView view;
	view.rootContext()->setContextProperty("gImGuiLines", pLines);
	view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile(QString("C:\\Users\\Kovalev\\Documents\\414135\\main.qml")));
	view.show();
	/*
	QQmlContext* thisContext = engine.rootContext();
	thisContext->setContextProperty("gImGuiLines", new ImGuiLines);
	engine.load((QUrl::fromLocalFile(QString("C:\\Users\\Kovalev\\Documents\\414135\\main.qml"))));
	*/

	return app.exec();
}
