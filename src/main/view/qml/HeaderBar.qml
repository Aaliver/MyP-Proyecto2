import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ToolBar {
    id: headerBar
    height: 50

    Material.accent: Material.BlueGrey
    property var selectedData: null

    Boton {
        id: editButton
        width: 45
        height: 45
        anchors.left: parent.left
        anchors.leftMargin: 10
        iconSource: "qrc:/img/images/edit.svg"
        icon.color: "transparent"
        onClicked: {
            if (headerBar.selectedData !== null) {
                openEditor(EditDialog.Edit.Rola,
                           [
                               { name: "Título", display: "title" },
                               { name: "Artista", display: "performer" },
                               { name: "Album", display: "album" },
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
        id: addButton
        width: 45
        height: 45
        anchors.left: editButton.right
        anchors.leftMargin: 10
        iconSource: "qrc:/img/images/add.svg"
        icon.color: "transparent"
    }

    Boton {
        id: deleteButton
        width: 45
        height: 45
        anchors.left: addButton.right
        anchors.leftMargin: 10
        iconSource: "qrc:/img/images/trash.svg"
        icon.color: "transparent"
        onClicked: {
            if (selectedData !== null)
                controlador.eliminaRola(selectedData)
        }
    }

    Boton {
        id: searchButton
        width: 45
        height: 45
        anchors.right: mineButton.left
        anchors.rightMargin: 10
        iconSource: "qrc:/img/images/form.svg"
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
