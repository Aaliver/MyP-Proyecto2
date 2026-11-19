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
		openEditor(EditDialog.Edit.Rola,
			   [
			       { name: "Título", display: "title" },
			       { name: "Año", display: "year" },
			       { name: "Género", display: "genre" }
			   ])
	    }
	}
    }

    function openEditor(type, fields: var) {
	editor.edit = type
	editor.editData = selectedData
	editor.fields = fields
	editor.open()
    }

    EditDialog {
	id: editor

	onSaveData: (editType, values) => {
	    switch (editType) {
	    case EditDialog.Edit.Rola:
		controlador.actualizaRola(values)
		break
	    case EditDialog.Edit.Album:
		controlador.actualizaAlbum(values)
		break
	    case EditDialog.Edit.Artist:
		controlador.actualizaArtista(values)
		break
	    default:
	    }
	}
    }

    Boton {
	id: searchButton
	width: 45
        height: 45
	anchors.right: mineButton.left
	anchors.rightMargin: 10
	iconSource: "qrc:/img/images/search.svg"
	icon.color: "transparent"
	onClicked: search.open()
    }

    SearchForm {
	id: search

	onSearchData: (values) => { controlador.buscaRolas(values) }
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
