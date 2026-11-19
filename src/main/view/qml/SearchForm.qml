import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

Dialog {
    id: searchForm
    width: window.width / 3
    height: window.height / 2
    title: "Buscar Rolas"

    modal: true
    anchors.centerIn: Overlay.overlay
    standardButtons: Dialog.Ok | Dialog.Cancel

    signal searchData(var values)

    ListModel {
	id: searchModel
	ListElement { name: "Título"; field: "title"; search: "" }
	ListElement { name: "Año"; field: "year"; search: "" }
	ListElement { name: "Género"; field: "genre"; search: "" }
	ListElement { name: "Álbum"; field: "album"; search: "" }
	ListElement { name: "Artista"; field: "performer"; search: "" }
    }

    Loader {
	anchors.fill: parent
	active: searchForm.visible
	sourceComponent: component
    }

    Component {
	id: component

	ListView {
	    id: dataSearch
	    anchors.fill: parent
	    spacing: 5
	    clip: true

	    model: searchModel

	    delegate: Rectangle {
		id: listViewDelegate
		height: 50
		width: parent.width
		color: palette.midlight
		border.width: 0
		border.color: Material.accent
		radius: 5

		RowLayout {
		    id: row
		    anchors.left: parent.left
                    anchors.right: parent.right
		    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 5

		    TextField {
			Layout.fillWidth: true
			Layout.fillHeight: true

			font.pixelSize: 15
			placeholderText: model.name
			color: palette.text

			background: Rectangle {
			    color: palette.midlight
			}

			onActiveFocusChanged: {
			    listViewDelegate.border.width = activeFocus ? 2 : 0
			}

			onTextEdited: {
			    searchModel.setProperty(index, "search", text)
			}
                    }
		}
            }
	}
    }

    onAccepted: {
	let values = {}
        for (let i = 0; i < searchModel.count; ++i) {
            let element = searchModel.get(i)
            if (element.search.trim() !== "")
                values[element.field] = element.search.trim()
        }
        searchData(values)
    }
}
