import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ToolBar {
    id: headerBar
    height: 50

    Boton {
	width: 45
        height: 45
	anchors.left: parent.left
	anchors.leftMargin: 10
	iconSource: "qrc:/img/images/edit.png"
	icon.color: "transparent"
    }

    Boton {
	width: 45
        height: 45
	anchors.right: parent.right
	anchors.rightMargin: 10
	iconSource: "qrc:/img/images/pickaxe.png"
	icon.color: "transparent"
    }
}
