import QtQuick
import Qt.labs.qmlmodels
import QtQuick.Controls
import QtQuick.Controls.Material

Page {
    anchors.fill: parent
    anchors.margins: 10
    palette.text: "lavender"

    HorizontalHeaderView {
	id: rolasViewHeader
	height: 40
	anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

	syncView: rolasView
	clip: true

	delegate: Rectangle {
	    implicitWidth: 150
	    implicitHeight: 35
            color: palette.mid

	    Text {
		text: display
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
	    TableModelColumn { display: "name" }
	    TableModelColumn { display: "color" }

            rows: [
		{ "name": "cat", "color": "black" },
		{ "name": "dog", "color": "brown" },
		{ "name": "bird", "color": "white" }
            ]
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
