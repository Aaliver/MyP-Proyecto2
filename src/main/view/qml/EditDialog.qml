import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Dialog {
    id: editDialog
    width: window.width / 2.5
    height: window.height / 2

    modal: true
    anchors.centerIn: Overlay.overlay
    standardButtons: Dialog.Save | Dialog.Cancel

    property var data: null
    property var fields: []

    ListView {
	id: dataView
	anchors.fill: parent
	spacing: 5
	clip: true

	model: editDialog.fields

	delegate: Rectangle {
            height: 45
	    width: parent.width
            color: palette.midlight
            radius: 5

            RowLayout {
		anchors.left: parent.left
                anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 15
                spacing: 15

                Text {
		    text: modelData.name + ":"
		    color: edit.Material.accent
                }

		Text {
		    text: editDialog.data != null ?
			editDialog.data[modelData.display] : ""
		    color: palette.text
		}

		Item {
		    Layout.fillWidth: true
		}

                Boton {
		    id: edit
		    Layout.preferredWidth: 40
		    Layout.preferredHeight: 40
		    iconSource: "qrc:/img/images/pen.svg"
                }
            }
        }
    }
}
