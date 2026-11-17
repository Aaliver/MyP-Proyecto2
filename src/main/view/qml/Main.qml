import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    id: window
    visible: true
    visibility: "Maximized"
    width: 1000
    height: 700
    palette.text: "lavender"
    title: "Base de Datos Musical"

    Material.theme: Material.Dark
    Material.accent: Material.Indigo

    header: HeaderBar {
	selectedData: body.dataRow
    }

    Body { id: body }

    footer: FooterBar {
	selectedRola: body.dataRow
    }
}
