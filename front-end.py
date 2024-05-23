import flet as ft
from flet import (
    View,
    Text,
    AppBar,
    ElevatedButton,
    RouteChangeEvent,
    ViewPopEvent,
    CrossAxisAlignment,
    MainAxisAlignment,
    Container,
    TextField,
    ControlEvent,
    Switch,
    SearchBar,
    ListView,
    DataTable,
    Control,
    NavigationDrawer,
)
from flet_core import Theme
import json
import os
from datetime import datetime
import ctypes

senha = "senha"

def main(page: ft.Page) -> None:
    page.title = "Sistema de Estoque"
    page.drawer = ft.NavigationDrawer(controls=[
        ft.Container(height=12),
        ft.NavigationDrawerDestination(
            label="Produtos",
        )
    ])
    page.fonts = {
        "Roboto": "fonts/Roboto-Regular.ttf",
        "Montserrat ExtraLight": "fonts/Montserrat-ExtraLight.ttf"
    }
    page.theme = Theme(font_family="Roboto")

    def erro_campos(mensagem: str) -> None:
        def fechar_popup(self) -> None:
            erro_popup.open = False
            page.update()
        erro_popup = ft.AlertDialog(
            modal=True,
            title=ft.Text("Campos Vazios"),
            content=ft.Text(f"{mensagem}"),
            actions=[ft.TextButton(text="OK", on_click=fechar_popup)],
            actions_alignment=ft.MainAxisAlignment.CENTER
        )
        page.dialog = erro_popup
        erro_popup.open = True
        page.update()

    def validando(e: ControlEvent):
        if all([campo_nome.value, campo_senha.value]) and campo_senha.value == senha:
            data = datetime.now()
            hora = data.strftime("%H:%M:%S")
            login_data = {
                "nome": campo_nome.value,
                "Hora": hora
            }
            json_object = json.dumps(login_data, indent=2)
            with open(os.path.join("data", "user_data.json"), "w") as write_file:
                write_file.write(json_object)
            botao_entrar.disabled = False
        else:
            botao_entrar.disabled = True

        page.update()
    def dados_produtos_para_json() -> bool:
        id_produto = campo_id.value
        nome_produto = campo_nome_produto.value
        preco_produto = campo_preco.value
        quantidade = campo_quantidade.value
        if all([campo_id, campo_nome_produto, campo_preco, campo_quantidade]):
            dados_produto = {
                "id": int(id_produto),
                "nome": nome_produto,
                "preco": float(preco_produto),
                "quantidade": quantidade
            }
            json_object = json.dumps(dados_produto, indent=4)
            with open(os.path.join("data", "product_data.json"), "w") as write_file:
                write_file.write(json_object)
            return True
        else:
            erro_campos("teste")

    def retirar_produtos(self) -> None:
        id_produto = campo_id.value
        quantidade = campo_quantidade.value
        if all([campo_id.value, campo_nome]):
            dados_retirar_produto = {
                "id": int(id_produto),
                "quantidade": int(quantidade)
            }
            json_object = json.dumps(dados_retirar_produto, indent=2)
            with open(os.path.join("data", "retirar_produtos_data.json"), "w") as write_file:
                write_file.write(json_object)
            return None
        else:
            erro_campos("Por favor, insira o Id e a quantidade do produto que deseja remover")

    def entrar(e: ControlEvent) -> None:
        page.go("/estoque")

    def entrar_historico(e: ControlEvent) -> None:
        page.go("/historico")

    def trocar_tema(e: ControlEvent) -> None:
        if page.theme_mode == ft.ThemeMode.LIGHT:
            page.theme_mode = ft.ThemeMode.DARK
            page.update()
        else:
            page.theme_mode = ft.ThemeMode.LIGHT
            page.update()

    def fechar_popup(self) -> None:
        popup.open = False
        page.update()

    popup = ft.AlertDialog(
        modal=False,
        title=ft.Text("Produto Adicionado"),
        content=ft.Text("O produto foi adicionado com sucesso!"),
        actions=[ft.TextButton(text="Ok", on_click=fechar_popup)],
        actions_alignment=ft.MainAxisAlignment.CENTER
    )
    def open_popuo() -> None:
        page.dialog = popup
        popup.open = True
        page.update()

    def combo_adicionar(self) -> None:
        if dados_produtos_para_json():
            open_popuo()
        else:
            return None

    def exibir_historico() -> Control:
        historico = 0 # isso é apenas para fins de teste enqt não tenho os dados do back-end
        if historico <=0:
            return ft.Text("Nenhuma ação por aqui 😀", size=25)
        else:
            return ft.Text(str(historico), size=25)

    ''' # esperando o back-end
    def excluir_produto() -> None:
    '''

    def paginas_drawer(e:ControlEvent) -> None:
        if e.control.selected_index == 0:
            page.go("/estoque")
            return None
        elif e.control.selected_index == 1:
            page.go("/historico")
            return None
        else:
            return None

    campo_nome: TextField = ft.TextField(
        label="Digite seu nome",
        width=400,
        hint_text="Ex: Maria Rosa",
        filled=True,
        on_change=validando
    )
    campo_senha: TextField = ft.TextField(
        label="Digite a senha",
        width=400,
        password=True,
        can_reveal_password=True,
        filled=True,
        on_change=validando
    )

    botao_entrar: ElevatedButton = ft.ElevatedButton(
        text="Entrar",
        disabled=True,
        on_click=entrar
    )

    botao_switch: Switch = ft.Switch(
        width=30,
        height=30,
        label="Dark Mode",
        value=True,
        on_change=trocar_tema,
    )

    drawer: NavigationDrawer = ft.NavigationDrawer(
        controls=[
            ft.Container(height=12),
            ft.NavigationDrawerDestination(
                label="Produtos",
                icon=ft.icons.SHOPPING_BAG,

            ),
            ft.NavigationDrawerDestination(
                label="Histórico",
                icon=ft.icons.HISTORY
            ),
            ft.Divider(thickness=2),
            ft.Container(
                content=botao_switch,
                alignment=ft.alignment.bottom_left,
                margin=5
            )
        ],
        tile_padding=5,
        selected_index=2,
        on_change=paginas_drawer
    )

    campo_id: TextField = ft.TextField(
        hint_text="ID:", width=100, height=50, border_color="Blue"
    )
    campo_nome_produto: TextField = ft.TextField(
        hint_text="Nome do Produto:", border_color="Blue", height=50
    )
    campo_quantidade: TextField = ft.TextField(
        hint_text="Quantidade:", width=150, height=50, border_color="Blue"
    )
    campo_preco: TextField = ft.TextField(
        hint_text="Preço:", width=150, height=50, border_color="Blue",
    )
    barra_pesquisa: SearchBar = ft.SearchBar(
        bar_hint_text="Busque por produtos do estoque",
        view_hint_text="Ex: Sapato",
        bar_leading=ft.IconButton(icon="search"),
        controls=[
            ft.ListTile(title=ft.Text(f"Teste"), data="teste"),
        ]
    )
    tabela_de_produtos: DataTable = ft.DataTable(
        width=1000,
        # bgcolor="#30343b",
        border_radius=10,
        show_checkbox_column=True,
        border=ft.border.all(1, "blue"),
        columns=[
            ft.DataColumn(ft.Text("ID")),
            ft.DataColumn(ft.Text("Nome")),
            ft.DataColumn(ft.Text("Quantidade")),
            ft.DataColumn(ft.Text("Preço")),
        ],
        rows=[
            ft.DataRow(
                cells=[
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                ],
                on_select_changed=lambda e: print("Teste"),
                on_long_press=None
            ),
            ft.DataRow(
                cells=[
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                ],
                on_select_changed=lambda e: print("Teste")
            ),
            ft.DataRow(
                cells=[
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                ],
                on_select_changed=lambda e: print("Teste")
            ),
            ft.DataRow(
                cells=[
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                ],
                on_select_changed=lambda e: print("Teste")
            ),
            ft.DataRow(
                cells=[
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                ],
                on_select_changed=lambda e: print("Teste")
            ),
            ft.DataRow(
                cells=[
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                    ft.DataCell(ft.Text("Placeholder")),
                ],
                on_select_changed=lambda e: print("Teste")
            ),
        ],
    )

    list : ListView = ft.ListView(expand=1, spacing=10, padding=20, auto_scroll=False)
    list.controls.append(tabela_de_produtos)

    def trocando_paginas(e: RouteChangeEvent) -> None:
        page.views.clear()
        page.window_width = 1000
        page.window_height = 700
        page.scroll = True
        page.add()

        # Página de Login
        page.views.append(
            View(
                route="/",
                controls=[AppBar(title=Text("Login"), bgcolor="blue", center_title=True),
                          ft.Text("BEM VINDO", font_family="Montserrat ExtraLight", size=30),
                          campo_nome,
                          campo_senha,
                          botao_entrar
                          ],
                # lambda _: page.go("/estoque")
                vertical_alignment=MainAxisAlignment.CENTER,
                horizontal_alignment=CrossAxisAlignment.CENTER,
                spacing=30,

            )
        )

        # Página do Estoque
        if page.route == "/estoque":
            page.views.append(
                View(
                    drawer=drawer,
                    route="/estoque",
                    controls=[AppBar(
                        title=Text("Gerenciamento do Estoque",
                                   font_family="Montserrat ExtraLight"),
                       # bgcolor="#30343b",
                        center_title=True, ),
                        Container(
                            content=ft.ElevatedButton("Histórico", icon=ft.icons.HISTORY, on_click=entrar_historico),
                            alignment=ft.alignment.top_right,
                            # bgcolor=ft.colors.RED
                        ),
                        ft.Text("Adicionar Produtos", font_family="Montserrat ExtraLight", size=20),
                        ft.Row(controls=[
                            campo_id,
                            campo_nome_produto,
                            campo_preco,
                            campo_quantidade,
                            ft.FloatingActionButton(icon=ft.icons.ADD, bgcolor="Blue", on_click=combo_adicionar),
                        ],
                            alignment=ft.MainAxisAlignment.CENTER,
                        ),
                        ft.Text("Retirar Produtos", font_family="Montserrat ExtraLight", size=20),
                        ft.Row(
                            controls=[
                                campo_id,
                                campo_quantidade,
                                ft.FloatingActionButton(icon=ft.icons.REMOVE, bgcolor="Red", on_click=retirar_produtos)
                            ],
                            alignment=ft.MainAxisAlignment.CENTER
                        ),
                        barra_pesquisa,
                        list,
                    ],

                    # vertical_alignment=MainAxisAlignment.CENTER,
                    horizontal_alignment=CrossAxisAlignment.CENTER,
                    # spacing=30
                )
            )
            page.add(drawer)
            page.update()
        # Página de Histórico
        elif page.route == "/historico":
            page.views.append(
                View(
                    drawer=drawer,
                    route="/historico",
                    controls=[AppBar(title=Text("Historico", font_family="Montserrat ExtraLight"),
                                    # bgcolor="#30343b",
                                     center_title=True,),
                              exibir_historico()
                              ],
                    vertical_alignment=MainAxisAlignment.CENTER,
                    horizontal_alignment=CrossAxisAlignment.CENTER,
                )
            )


    def view_pop(e: ViewPopEvent) -> None:
        page.views.pop()
        top_view: View = page.views[-1]
        page.go(top_view.route)

    page.on_route_change = trocando_paginas
    page.on_view_pop = view_pop
    page.go(page.route)


if __name__ == "__main__":
    ft.app(target=main, assets_dir="assets")
