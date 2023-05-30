from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter
from reportlab.lib.units import inch
from reportlab.lib import utils

# Dados da equipe
integrantes = [
    "Guilherme Iram",
    "Guilherme Pujoni",
    "Miqueias Luiz",
]

# Caminhos das imagens
imagens = [
    "tabelas/tabela_1_melhor_resultado.png",
    "tabelas/tabela_2_melhor_resultado.png",
    "tabelas/tabela_3_melhor_resultado.png",
    "tabelas/tabela_4_melhor_resultado.png",
    "tabelas/tabela_5_melhor_resultado.png",
    "tabelas/tabela_6_melhor_resultado.png",
    "tabelas/tabela_7_melhor_resultado.png",
    "tabelas/tabela_8_melhor_resultado.png",
    "tabelas/tabela_9_melhor_resultado.png",
    "tabelas/tabela_10_melhor_resultado.png"
]

# Criação do PDF
pdf_path = "Relatorio_projeto_final_APA.pdf"
c = canvas.Canvas(pdf_path, pagesize=letter)

# Escrita dos integrantes da equipe
c.setFont("Helvetica", 14)
c.drawString(1 * inch, 10 * inch, "Equipe de Desenvolvedores:")
c.setFont("Helvetica-Bold", 12)
y = 9.5 * inch
for integrante in integrantes:
    c.drawString(1 * inch, y, integrante)
    y -= 0.5 * inch

# Título das tabelas
c.setFont("Helvetica-Bold", 14)
c.drawString(1 * inch, y - 0.5 * inch, "Tabela dos 10 melhores resultados obtidos:")

letter = list(letter)
letter[1] = letter[1] - 4.5 * inch
letter = tuple(letter)

# Inserção das tabelas em páginas separadas
page_width, page_height = letter
table_margin = 0.5 * inch  # Margem ao redor da tabela
table_height = page_height - 4 * inch  # Altura da tabela

x = 1 * inch
y = 1 * inch

for i in range(0, len(imagens), 2):
    c.showPage()

    img = utils.ImageReader(imagens[i])
    img_width, img_height = img.getSize()

    aspect_ratio = img_height / float(img_width)
    table_width = table_height / aspect_ratio

    x_offset = (page_width - table_width) / 2
    y_offset = (page_height - table_height) * 3.5 / 2
    c.drawImage(imagens[i], x_offset, y_offset, width=table_width, height=table_height)

    img = utils.ImageReader(imagens[i + 1])
    img_width, img_height = img.getSize()

    aspect_ratio = img_height / float(img_width)
    table_width = table_height / aspect_ratio

    x_offset = (page_width - table_width) / 2
    y_offset = (page_height - table_height) * 1.5 / 2
    c.drawImage(imagens[i + 1], x_offset, y_offset, width=table_width, height=table_height)



# Salvando o PDF
c.showPage()
c.save()

print("PDF criado com sucesso!")
