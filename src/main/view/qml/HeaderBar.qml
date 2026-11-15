import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ToolBar {
    id: headerBar
    height: 50

    property var selectedData: null

    Boton {
	width: 45
        height: 45
	anchors.left: parent.left
	anchors.leftMargin: 10
	iconSource: "qrc:/img/images/edit.png"
	icon.color: "transparent"
	onClicked: {
	    if (headerBar.selectedData != null) {
		editRola.data = headerBar.selectedData
		editRola.open()
	    }
	}
    }

    EditDialog {
	id: editRola
	fields: [
            { name: "Título", display: "title" },
            { name: "Año", display: "year" },
            { name: "Género", display: "genre" }
	]
    }

    SearchField {
	width: parent.width / 3
        height: 30
	anchors.right: mineButton.left
	anchors.rightMargin: 10
	anchors.verticalCenter: parent.verticalCenter

	placeholderText: "Buscar..."
    }

    Boton {
	id: mineButton
	width: 45
        height: 45
	anchors.right: parent.right
	anchors.rightMargin: 10
	iconSource: "qrc:/img/images/pickaxe.png"
	icon.color: "transparent"
	onClicked: controlador.minar()
    }
}
