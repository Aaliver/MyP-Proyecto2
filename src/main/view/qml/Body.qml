import QtQuick
import Qt.labs.qmlmodels
import QtQuick.Controls
import QtQuick.Controls.Material

Page {
    anchors.fill: parent
    anchors.margins: 10

    property var dataRow: rolasView.currentRow >= 0
        ? controlador.rolas[rolasView.currentRow] : null

    HorizontalHeaderView {
	id: rolasViewHeader
	height: 40
	anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

	syncView: rolasView
	clip: true
	model: ["Titulo", "Album", "Año", "Género"]

	delegate: Rectangle {
	    implicitWidth: 150
	    implicitHeight: 35
            color: palette.mid

	    Text {
		text: modelData
		color: palette.text
		font.bold: true
		anchors.left: parent.left
		anchors.margins: 10
		anchors.verticalCenter: parent.verticalCenter
	    }
	}
    }

    TableView {
	id: rolasView
	anchors.left: parent.left
        anchors.right: parent.right
	anchors.top: rolasViewHeader.bottom
	anchors.bottom: parent.bottom

	columnSpacing: 0
	rowSpacing: 2
	clip: true
	interactive: true

	columnWidthProvider: function(column) {
	    switch (column) {
            case 0: return width * 0.40
            case 1: return width * 0.25
            case 2: return width * 0.10
	    case 3: return width * 0.25
            default: return 100
	    }
	}

	selectionBehavior: TableView.SelectRows
	selectionMode: TableView.SingleSelection
	selectionModel: ItemSelectionModel {
	    model: rolasView.model
	}

	ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
	    width: 5
	}

	ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOff
	}

	model: TableModel {
	    TableModelColumn { display: "title" }
	    TableModelColumn { display: "album" }
	    TableModelColumn { display: "year" }
	    TableModelColumn { display: "genre" }

            rows: Array.from(controlador.rolas)
	}

	delegate: Rectangle {
            implicitWidth: 150
            implicitHeight: 35
            border.width: 0
	    color: clicked ? "slateblue" : palette.mid

	    required property int row
	    property bool clicked: row === rolasView.currentRow

            Text {
		text: model.display
		color: palette.text
		font.bold: clicked
		anchors.left: parent.left
		anchors.margins: 10
		anchors.verticalCenter: parent.verticalCenter
            }
	}
    }
}
