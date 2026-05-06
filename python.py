from reportlab.lib.pagesizes import A4
from reportlab.lib import colors
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import cm, mm
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle,
    PageBreak, HRFlowable, KeepTogether
)
from reportlab.lib.enums import TA_CENTER, TA_LEFT, TA_JUSTIFY
from reportlab.platypus import Flowable

W, H = A4

# ── colour palette ────────────────────────────────────────────────────────────
DARK_BLUE   = colors.HexColor("#0D2137")
MID_BLUE    = colors.HexColor("#1A3F66")
ACCENT_BLUE = colors.HexColor("#2979B8")
LIGHT_BLUE  = colors.HexColor("#D6E8FA")
TEAL        = colors.HexColor("#1A7F8E")
LIGHT_TEAL  = colors.HexColor("#D0F0F5")
GOLD        = colors.HexColor("#C8901A")
GOLD_BG     = colors.HexColor("#FFF8E7")
RED         = colors.HexColor("#B03030")
RED_BG      = colors.HexColor("#FDE8E8")
GREEN       = colors.HexColor("#1A7A3C")
GREEN_BG    = colors.HexColor("#E8F5EE")
PURPLE      = colors.HexColor("#5B2C8D")
PURPLE_BG   = colors.HexColor("#F0E8FA")
GREY_LIGHT  = colors.HexColor("#F4F6F9")
GREY_MID    = colors.HexColor("#C8D0D8")
WHITE       = colors.white
BLACK       = colors.black

# ── styles ────────────────────────────────────────────────────────────────────
def make_styles():
    base = getSampleStyleSheet()
    s = {}

    s['cover_title'] = ParagraphStyle('cover_title',
        fontName='Helvetica-Bold', fontSize=28, textColor=WHITE,
        alignment=TA_CENTER, spaceAfter=6, leading=34)

    s['cover_sub'] = ParagraphStyle('cover_sub',
        fontName='Helvetica', fontSize=13, textColor=colors.HexColor("#B8D4F0"),
        alignment=TA_CENTER, spaceAfter=4, leading=18)

    s['cover_info'] = ParagraphStyle('cover_info',
        fontName='Helvetica', fontSize=11, textColor=WHITE,
        alignment=TA_CENTER, spaceAfter=3, leading=15)

    s['h1'] = ParagraphStyle('h1',
        fontName='Helvetica-Bold', fontSize=20, textColor=WHITE,
        alignment=TA_LEFT, spaceAfter=4, spaceBefore=2, leading=24,
        leftIndent=0)

    s['h2'] = ParagraphStyle('h2',
        fontName='Helvetica-Bold', fontSize=15, textColor=DARK_BLUE,
        spaceAfter=6, spaceBefore=10, leading=19,
        borderPad=4)

    s['h3'] = ParagraphStyle('h3',
        fontName='Helvetica-Bold', fontSize=12, textColor=MID_BLUE,
        spaceAfter=4, spaceBefore=7, leading=16)

    s['h4'] = ParagraphStyle('h4',
        fontName='Helvetica-Bold', fontSize=11, textColor=TEAL,
        spaceAfter=3, spaceBefore=5, leading=14)

    s['body'] = ParagraphStyle('body',
        fontName='Helvetica', fontSize=10, textColor=BLACK,
        spaceAfter=5, spaceBefore=2, leading=15, alignment=TA_JUSTIFY)

    s['body_bold'] = ParagraphStyle('body_bold',
        fontName='Helvetica-Bold', fontSize=10, textColor=BLACK,
        spaceAfter=4, spaceBefore=2, leading=14)

    s['formula'] = ParagraphStyle('formula',
        fontName='Helvetica-Bold', fontSize=10.5, textColor=DARK_BLUE,
        spaceAfter=3, spaceBefore=3, leading=15, alignment=TA_CENTER)

    s['formula_label'] = ParagraphStyle('formula_label',
        fontName='Helvetica-BoldOblique', fontSize=9.5, textColor=ACCENT_BLUE,
        spaceAfter=1, spaceBefore=1, leading=13, alignment=TA_CENTER)

    s['bullet'] = ParagraphStyle('bullet',
        fontName='Helvetica', fontSize=10, textColor=BLACK,
        spaceAfter=3, spaceBefore=1, leading=14, leftIndent=16,
        bulletIndent=4)

    s['bullet_bold'] = ParagraphStyle('bullet_bold',
        fontName='Helvetica-Bold', fontSize=10, textColor=BLACK,
        spaceAfter=3, spaceBefore=1, leading=14, leftIndent=16,
        bulletIndent=4)

    s['note'] = ParagraphStyle('note',
        fontName='Helvetica-Oblique', fontSize=9.5, textColor=colors.HexColor("#444444"),
        spaceAfter=3, spaceBefore=2, leading=14, leftIndent=10)

    s['table_header'] = ParagraphStyle('table_header',
        fontName='Helvetica-Bold', fontSize=9.5, textColor=WHITE,
        alignment=TA_CENTER, leading=13)

    s['table_cell'] = ParagraphStyle('table_cell',
        fontName='Helvetica', fontSize=9.5, textColor=BLACK,
        alignment=TA_CENTER, leading=13)

    s['table_cell_left'] = ParagraphStyle('table_cell_left',
        fontName='Helvetica', fontSize=9.5, textColor=BLACK,
        alignment=TA_LEFT, leading=13)

    s['toc_entry'] = ParagraphStyle('toc_entry',
        fontName='Helvetica', fontSize=10.5, textColor=DARK_BLUE,
        spaceAfter=4, spaceBefore=2, leading=15)

    s['toc_sub'] = ParagraphStyle('toc_sub',
        fontName='Helvetica', fontSize=9.5, textColor=MID_BLUE,
        spaceAfter=2, spaceBefore=1, leading=13, leftIndent=20)

    s['example_title'] = ParagraphStyle('example_title',
        fontName='Helvetica-Bold', fontSize=10.5, textColor=GREEN,
        spaceAfter=3, spaceBefore=2, leading=14)

    s['warning'] = ParagraphStyle('warning',
        fontName='Helvetica-Bold', fontSize=10, textColor=RED,
        spaceAfter=3, spaceBefore=2, leading=14)

    return s

# ── helper flowables ──────────────────────────────────────────────────────────
class ColoredBox(Flowable):
    def __init__(self, content_flowables, bg_color, border_color=None,
                 padding=8, radius=4):
        Flowable.__init__(self)
        self.content = content_flowables
        self.bg = bg_color
        self.border = border_color or bg_color
        self.padding = padding
        self.radius = radius

    def wrap(self, avail_w, avail_h):
        self.avail_w = avail_w
        return avail_w, 0   # height computed in draw

    def draw(self):
        pass   # we won't use this directly; use inline tables instead


def section_header(title, s, color=MID_BLUE, bg=LIGHT_BLUE):
    """Returns a table that looks like a coloured section header."""
    data = [[Paragraph(title, s['h2'])]]
    t = Table(data, colWidths=[W - 4*cm])
    t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,-1), bg),
        ('LEFTPADDING', (0,0), (-1,-1), 10),
        ('RIGHTPADDING', (0,0), (-1,-1), 10),
        ('TOPPADDING', (0,0), (-1,-1), 6),
        ('BOTTOMPADDING', (0,0), (-1,-1), 6),
        ('LINEBELOW', (0,0), (-1,-1), 2, color),
        ('ROWBACKGROUNDS', (0,0), (-1,-1), [bg]),
    ]))
    return t


def formula_box(lines, s, bg=GOLD_BG, border=GOLD):
    """Render formula lines in a nicely coloured box."""
    rows = [[Paragraph(l, s['formula'])] for l in lines]
    t = Table(rows, colWidths=[W - 4*cm])
    t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,-1), bg),
        ('LEFTPADDING', (0,0), (-1,-1), 10),
        ('RIGHTPADDING', (0,0), (-1,-1), 10),
        ('TOPPADDING', (0,0), (-1,-1), 6),
        ('BOTTOMPADDING', (0,0), (-1,-1), 6),
        ('BOX', (0,0), (-1,-1), 1.5, border),
        ('LINEABOVE', (0,0), (-1,0), 2.5, border),
    ]))
    return t


def note_box(text, s, bg=PURPLE_BG, border=PURPLE):
    data = [[Paragraph(text, s['body'])]]
    t = Table(data, colWidths=[W - 4*cm])
    t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,-1), bg),
        ('LEFTPADDING', (0,0), (-1,-1), 10),
        ('RIGHTPADDING', (0,0), (-1,-1), 10),
        ('TOPPADDING', (0,0), (-1,-1), 6),
        ('BOTTOMPADDING', (0,0), (-1,-1), 6),
        ('LINEBEFORE', (0,0), (0,-1), 4, border),
    ]))
    return t


def example_box(title, rows_text, s):
    """Green-tinted example/solved-problem box."""
    inner = [Paragraph(title, s['example_title'])]
    for r in rows_text:
        inner.append(Paragraph(r, s['body']))
    cells = [[p] for p in inner]
    t = Table(cells, colWidths=[W - 4*cm])
    t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,-1), GREEN_BG),
        ('LEFTPADDING', (0,0), (-1,-1), 10),
        ('RIGHTPADDING', (0,0), (-1,-1), 10),
        ('TOPPADDING', (0,0), (-1,-1), 5),
        ('BOTTOMPADDING', (0,0), (-1,-1), 5),
        ('BOX', (0,0), (-1,-1), 1, GREEN),
        ('LINEABOVE', (0,0), (-1,0), 2.5, GREEN),
    ]))
    return t


def chapter_banner(num, title, s):
    """Full-width dark banner for chapter headings."""
    data = [[Paragraph(f"CHAPTER {num}   |   {title}", s['h1'])]]
    t = Table(data, colWidths=[W - 4*cm])
    t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,-1), DARK_BLUE),
        ('LEFTPADDING', (0,0), (-1,-1), 16),
        ('TOPPADDING', (0,0), (-1,-1), 10),
        ('BOTTOMPADDING', (0,0), (-1,-1), 10),
        ('RIGHTPADDING', (0,0), (-1,-1), 16),
    ]))
    return t


def two_col_table(headers, rows, s, col_widths=None):
    if col_widths is None:
        col_widths = [(W - 4*cm) / len(headers)] * len(headers)
    data = [[Paragraph(h, s['table_header']) for h in headers]]
    for r in rows:
        data.append([Paragraph(str(c), s['table_cell']) for c in r])
    t = Table(data, colWidths=col_widths, repeatRows=1)
    t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,0), MID_BLUE),
        ('ROWBACKGROUNDS', (0,1), (-1,-1), [GREY_LIGHT, WHITE]),
        ('GRID', (0,0), (-1,-1), 0.5, GREY_MID),
        ('TOPPADDING', (0,0), (-1,-1), 5),
        ('BOTTOMPADDING', (0,0), (-1,-1), 5),
        ('LEFTPADDING', (0,0), (-1,-1), 6),
        ('RIGHTPADDING', (0,0), (-1,-1), 6),
        ('VALIGN', (0,0), (-1,-1), 'MIDDLE'),
    ]))
    return t


def sp(n=1):
    return Spacer(1, n * 4 * mm)


# ══════════════════════════════════════════════════════════════════════════════
#  DOCUMENT BUILD
# ══════════════════════════════════════════════════════════════════════════════
def build_pdf(path):
    doc = SimpleDocTemplate(
        path, pagesize=A4,
        leftMargin=2*cm, rightMargin=2*cm,
        topMargin=2.2*cm, bottomMargin=2.2*cm,
        title="Queueing Models – Final Exam Notes",
        author="SE Fundamentals Study Guide"
    )
    s = make_styles()
    story = []

    # ── COVER PAGE ────────────────────────────────────────────────────────────
    cover_data = [[
        Paragraph("SOFTWARE ENGINEERING FUNDAMENTALS", s['cover_sub']),
        Paragraph("Queueing Models", s['cover_title']),
        Paragraph("Complete Final Exam Study Notes", s['cover_sub']),
        Spacer(1, 6*mm),
        Paragraph("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", s['cover_info']),
        Spacer(1, 4*mm),
        Paragraph("Topics Covered", s['cover_sub']),
        Paragraph("Foundations of Queueing Theory  •  Kendall Notation  •  M/M/1  •  M/M/c (Multi-Server)", s['cover_info']),
        Paragraph("M/G/1  •  G/G/1  •  Simulation of M/M/1 and M/M/2  •  Solved Examples", s['cover_info']),
        Spacer(1, 6*mm),
        Paragraph("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", s['cover_info']),
    ]]
    cover_t = Table(cover_data, colWidths=[W - 4*cm])
    cover_t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,-1), DARK_BLUE),
        ('LEFTPADDING', (0,0), (-1,-1), 30),
        ('RIGHTPADDING', (0,0), (-1,-1), 30),
        ('TOPPADDING', (0,0), (-1,-1), 60),
        ('BOTTOMPADDING', (0,0), (-1,-1), 60),
    ]))
    story.append(cover_t)
    story.append(PageBreak())

    # ── TABLE OF CONTENTS ─────────────────────────────────────────────────────
    story.append(chapter_banner("TOC", "TABLE OF CONTENTS", s))
    story.append(sp(2))
    toc = [
        ("1", "Foundations of Queueing Theory", [
            "1.1 What is a Queue?",
            "1.2 Components of a Queueing System",
            "1.3 Key Performance Metrics",
            "1.4 Little's Law",
            "1.5 Traffic Intensity (Utilisation)",
            "1.6 Kendall Notation A/B/c/K/N/D",
        ]),
        ("2", "Poisson Process and Exponential Distribution", [
            "2.1 Poisson Arrivals",
            "2.2 Exponential Service Times",
            "2.3 Memoryless Property",
            "2.4 Birth-Death Process",
        ]),
        ("3", "M/M/1 Queue — Single Server", [
            "3.1 Model Assumptions",
            "3.2 Complete Formula Sheet",
            "3.3 Derivation of Key Formulas",
            "3.4 State Probabilities",
            "3.5 Solved Examples",
        ]),
        ("4", "M/M/c Queue — Multi-Server", [
            "4.1 Model Assumptions",
            "4.2 Erlang-C Formula",
            "4.3 Complete Formula Sheet",
            "4.4 Solved Examples",
        ]),
        ("5", "M/G/1 Queue — General Service", [
            "5.1 Model Assumptions",
            "5.2 Pollaczek-Khinchine (P-K) Formula",
            "5.3 Complete Formula Sheet",
            "5.4 Derivation Notes",
            "5.5 Solved Examples",
        ]),
        ("6", "G/G/1 Queue — General Arrivals and Service", [
            "6.1 Model Assumptions",
            "6.2 Kingman's (VUT) Approximation",
            "6.3 Bounds and Approximations",
            "6.4 Solved Examples",
        ]),
        ("7", "Simulation of M/M/1 and M/M/2 Queues", [
            "7.1 Why Simulate?",
            "7.2 Event-Driven Simulation Mechanics",
            "7.3 Random Variate Generation",
            "7.4 Step-by-Step Simulation of M/M/1",
            "7.5 Step-by-Step Simulation of M/M/2",
            "7.6 Performance Estimation from Simulation",
        ]),
        ("8", "Comparative Summary and Exam Tips", [
            "8.1 Model Comparison Table",
            "8.2 Formula Quick-Reference",
            "8.3 Common Exam Question Types",
            "8.4 Pitfalls and Tricks",
        ]),
    ]
    for num, title, subs in toc:
        story.append(Paragraph(f"<b>Chapter {num}  —  {title}</b>", s['toc_entry']))
        for sub in subs:
            story.append(Paragraph(f"• {sub}", s['toc_sub']))
        story.append(sp())
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 1: FOUNDATIONS
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("1", "FOUNDATIONS OF QUEUEING THEORY", s))
    story.append(sp(2))

    story.append(section_header("1.1  What is a Queue?", s))
    story.append(sp())
    story.append(Paragraph(
        "A <b>queue</b> (or waiting line) forms whenever demand for a service temporarily "
        "exceeds the capacity of a service facility. Queueing Theory is the mathematical "
        "study of these waiting lines. It enables us to predict and optimise performance "
        "metrics such as average waiting time, queue length, and resource utilisation.",
        s['body']))
    story.append(Paragraph(
        "Queueing theory originated with <b>A.K. Erlang</b> (1909), a Danish engineer at "
        "the Copenhagen Telephone Exchange, who derived the first closed-form results for "
        "telephone traffic congestion. Today, it is central to the design of operating "
        "systems, computer networks, manufacturing lines, healthcare systems, and "
        "transportation networks.", s['body']))
    story.append(sp())

    story.append(section_header("1.2  Components of a Queueing System", s))
    story.append(sp())
    story.append(Paragraph("<b>The five fundamental components are:</b>", s['body_bold']))
    comps = [
        ("Arrival Process", "Describes how customers (jobs, packets, calls …) arrive. "
            "Characterised by the inter-arrival time distribution. If exponential → Poisson "
            "arrivals with rate λ (lambda) customers per unit time."),
        ("Service Mechanism", "The number of servers (channels) and the service-time distribution "
            "for each server. Mean service rate = μ (mu) customers per unit time per server."),
        ("Queue Discipline", "The rule that determines which waiting customer is served next. "
            "Common disciplines: FCFS / FIFO (First-Come First-Served), LCFS (Last-Come "
            "First-Served), SIRO (Service In Random Order), Priority (preemptive or non-preemptive)."),
        ("System Capacity (K)", "Maximum number of customers allowed in the system (waiting + being "
            "served). If K = ∞ the system has unlimited capacity."),
        ("Population Size (N)", "The total pool of potential customers. If finite, arriving rate "
            "depends on how many are already in the system."),
    ]
    for term, desc in comps:
        story.append(Paragraph(f"<b>• {term}:</b> {desc}", s['bullet']))
    story.append(sp())

    story.append(section_header("1.3  Key Performance Metrics", s))
    story.append(sp())
    metrics_headers = ["Symbol", "Name", "Meaning"]
    metrics_rows = [
        ["λ  (lambda)", "Arrival Rate", "Average number of customers arriving per unit time"],
        ["μ  (mu)", "Service Rate", "Average number of customers served per unit time per server"],
        ["ρ  (rho)", "Traffic Intensity / Utilisation", "ρ = λ / (c·μ) — fraction of time server(s) busy"],
        ["L", "Mean number in system", "Average customers in system (waiting + in service)"],
        ["Lq", "Mean queue length", "Average customers waiting (not being served)"],
        ["W", "Mean sojourn time", "Average total time a customer spends in the system"],
        ["Wq", "Mean waiting time", "Average time a customer spends waiting in queue"],
        ["P0", "Idle probability", "Probability that system is empty (all servers idle)"],
        ["Pn", "State probability", "Probability that exactly n customers are in system"],
        ["Pb / Pc", "Blocking / Delay probability", "Prob. an arriving customer is blocked / must wait"],
    ]
    story.append(two_col_table(metrics_headers, metrics_rows, s,
                               col_widths=[3*cm, 5.5*cm, 8.2*cm]))
    story.append(sp(2))

    story.append(section_header("1.4  Little's Law  (Fundamental Theorem of Queueing)", s))
    story.append(sp())
    story.append(Paragraph(
        "Little's Law is the single most important identity in queueing theory. It holds "
        "for <b>any</b> stable queueing system regardless of arrival distribution, service "
        "distribution, number of servers, or queue discipline — provided the system is in "
        "<b>steady state</b>.", s['body']))
    story.append(sp())
    story.append(formula_box([
        "L  =  λ · W",
        "Lq  =  λ · Wq",
        "W  =  Wq  +  1/μ",
    ], s))
    story.append(sp())
    story.append(Paragraph(
        "<b>Interpretation:</b> The average number of customers in the system equals the "
        "average arrival rate multiplied by the average time each customer spends in the "
        "system. These three relationships let you derive any one metric from the other two.",
        s['body']))
    story.append(note_box(
        "⚠ Exam Tip: Whenever you know L or Lq and λ, use Little's Law immediately to get "
        "W or Wq. Almost every queueing exam question uses this relationship.", s))
    story.append(sp(2))

    story.append(section_header("1.5  Traffic Intensity / Server Utilisation (ρ)", s))
    story.append(sp())
    story.append(Paragraph(
        "Traffic intensity ρ measures how 'loaded' the system is. For <b>stability</b> "
        "(so that a steady-state exists and the queue does not grow without bound) we require "
        "ρ < 1 (for single-server) or ρ/c < 1 (for c-server).", s['body']))
    story.append(formula_box([
        "Single server:   ρ = λ / μ         (must be < 1 for stability)",
        "c servers:       ρ = λ / (c · μ)   (must be < 1 for stability)",
        "Alternatively:   ρ = λ · E[S]      where E[S] = mean service time = 1/μ",
    ], s))
    story.append(sp())
    story.append(Paragraph(
        "ρ also equals the <b>long-run fraction of time a server is busy</b>. "
        "If ρ = 0.8 the server is busy 80 % of the time.", s['body']))
    story.append(sp(2))

    story.append(section_header("1.6  Kendall's Notation  A/B/c/K/N/D", s))
    story.append(sp())
    story.append(Paragraph(
        "David Kendall (1953) introduced a compact notation to classify queues:",
        s['body']))
    story.append(sp())
    ken_headers = ["Position", "Symbol", "Meaning", "Common Values"]
    ken_rows = [
        ["1st", "A", "Inter-arrival time distribution", "M = Markovian/Exponential, G = General, D = Deterministic, Ek = Erlang-k"],
        ["2nd", "B", "Service time distribution", "M = Exponential, G = General, D = Deterministic, H = Hyperexponential"],
        ["3rd", "c", "Number of parallel servers", "1, 2, 3, … , c (integer ≥ 1)"],
        ["4th", "K", "System capacity (max customers)", "Finite integer or ∞ (default = ∞)"],
        ["5th", "N", "Population size (calling source)", "Finite integer or ∞ (default = ∞)"],
        ["6th", "D", "Queue discipline", "FCFS (default), LCFS, SIRO, PR (priority)"],
    ]
    story.append(two_col_table(ken_headers, ken_rows, s,
        col_widths=[1.8*cm, 1.5*cm, 4.5*cm, 8.9*cm]))
    story.append(sp())
    story.append(Paragraph(
        "<b>Examples:</b> M/M/1 = Poisson arrivals, exponential service, 1 server, infinite "
        "capacity, infinite population, FCFS. &nbsp; M/G/1 = Poisson arrivals, general "
        "service, 1 server. &nbsp; G/G/1 = general arrivals, general service, 1 server.", s['body']))
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 2: POISSON & EXPONENTIAL
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("2", "POISSON PROCESS & EXPONENTIAL DISTRIBUTION", s))
    story.append(sp(2))

    story.append(section_header("2.1  Poisson Arrivals", s))
    story.append(sp())
    story.append(Paragraph(
        "A <b>Poisson process</b> with rate λ is the most common model for arrivals in "
        "queueing systems. It arises naturally as the superposition of many independent "
        "rare events.", s['body']))
    story.append(Paragraph("<b>Key properties of the Poisson process:</b>", s['body_bold']))
    story.append(Paragraph("• Stationary: probability of k arrivals in [t, t+s] depends only on s, not t.", s['bullet']))
    story.append(Paragraph("• Independent increments: arrivals in non-overlapping intervals are independent.", s['bullet']))
    story.append(Paragraph("• Orderliness: probability of two simultaneous arrivals is negligible.", s['bullet']))
    story.append(sp())
    story.append(Paragraph("<b>Probability of k arrivals in time interval t:</b>", s['body_bold']))
    story.append(formula_box([
        "P(N(t) = k)  =  (λt)<super>k</super> · e<super>-λt</super>  /  k!      k = 0, 1, 2, …",
        "E[N(t)] = λt          Var[N(t)] = λt",
    ], s))
    story.append(sp())
    story.append(Paragraph(
        "<b>PASTA Property (Poisson Arrivals See Time Averages):</b> For a Poisson arrival "
        "process, an arriving customer sees the system in the same time-average state as an "
        "outside observer. That is, the probability that an arriving customer finds n customers "
        "in the system equals Pn, the steady-state probability. This extremely useful property "
        "holds <i>only</i> for Poisson arrivals.", s['body']))
    story.append(sp(2))

    story.append(section_header("2.2  Exponential Service Times", s))
    story.append(sp())
    story.append(Paragraph(
        "When service times follow an <b>exponential distribution</b> with parameter μ:", s['body']))
    story.append(formula_box([
        "PDF:   f(x) = μ · e<super>-μx</super>          x ≥ 0",
        "CDF:   F(x) = 1 − e<super>-μx</super>",
        "Mean:  E[S] = 1/μ",
        "Variance:  Var[S] = 1/μ<super>2</super>",
        "Coefficient of Variation:  C<sub>s</sub><super>2</super> = Var[S] / (E[S])<super>2</super> = 1   (always = 1 for exponential)",
    ], s))
    story.append(sp(2))

    story.append(section_header("2.3  Memoryless (Markov) Property", s))
    story.append(sp())
    story.append(Paragraph(
        "The exponential distribution is the <i>only</i> continuous distribution with the "
        "<b>memoryless property</b>:", s['body']))
    story.append(formula_box([
        "P(S > s + t  |  S > t)  =  P(S > s)     for all s, t ≥ 0",
    ], s))
    story.append(Paragraph(
        "Interpretation: If a customer has already been in service for time t, the remaining "
        "service time has exactly the same distribution as a fresh service time. The server "
        "has 'no memory' of the past. This is what makes M/M queues analytically tractable.",
        s['body']))
    story.append(sp(2))

    story.append(section_header("2.4  Birth-Death Process", s))
    story.append(sp())
    story.append(Paragraph(
        "The <b>birth-death process</b> is a special continuous-time Markov chain used as "
        "the foundation for all M/M/· queues. The state n = number of customers in system.",
        s['body']))
    story.append(Paragraph("<b>Transition rates:</b>", s['body_bold']))
    story.append(Paragraph("• Birth rate (arrival) in state n: λ<sub>n</sub>  (rate at which state n → n+1)", s['bullet']))
    story.append(Paragraph("• Death rate (departure) in state n: μ<sub>n</sub>  (rate at which state n → n-1)", s['bullet']))
    story.append(sp())
    story.append(Paragraph("<b>Balance Equations (Global Balance):</b>", s['body_bold']))
    story.append(formula_box([
        "λ<sub>n</sub> · P<sub>n</sub>  =  μ<sub>n+1</sub> · P<sub>n+1</sub>       n = 0, 1, 2, …  (Local / Detailed Balance)",
        "Σ P<sub>n</sub>  =  1      (Normalisation condition, sum over all n ≥ 0)",
    ], s))
    story.append(Paragraph(
        "Solving the local balance equations recursively gives Pn in terms of P0. Then "
        "normalisation pins P0. From {Pn} all other metrics (L, Lq, W, Wq) follow.",
        s['body']))
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 3: M/M/1
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("3", "M/M/1 QUEUE — SINGLE SERVER", s))
    story.append(sp(2))

    story.append(section_header("3.1  Model Assumptions", s))
    story.append(sp())
    for a in [
        "Arrivals follow a Poisson process with rate λ (inter-arrival times ~ Exp(λ)).",
        "Service times are independently and identically distributed (iid) Exponential with parameter μ (mean service time = 1/μ).",
        "Single server (c = 1).",
        "Infinite waiting room (K = ∞).",
        "Infinite population (N = ∞).",
        "Queue discipline: FCFS (results identical for any work-conserving discipline).",
        "System must be stable: ρ = λ/μ < 1.  If ρ ≥ 1, queue grows without bound.",
    ]:
        story.append(Paragraph(f"• {a}", s['bullet']))
    story.append(sp(2))

    story.append(section_header("3.2  Complete M/M/1 Formula Sheet", s))
    story.append(sp())
    story.append(formula_box([
        "Traffic Intensity:    ρ = λ / μ           (stability condition: ρ < 1)",
        "",
        "State probabilities:  P<sub>0</sub> = 1 − ρ",
        "                      P<sub>n</sub> = (1 − ρ) · ρ<super>n</super>      n = 0, 1, 2, …",
        "",
        "Mean number in system:     L  =  ρ / (1 − ρ)  =  λ / (μ − λ)",
        "",
        "Mean queue length:         L<sub>q</sub>  =  ρ<super>2</super> / (1 − ρ)  =  λ<super>2</super> / [μ(μ − λ)]",
        "",
        "Relationship:              L  =  L<sub>q</sub> + ρ      (ρ = mean number in service)",
        "",
        "Mean time in system:       W  =  1 / (μ − λ)  =  L / λ",
        "",
        "Mean waiting time in queue: W<sub>q</sub>  =  ρ / (μ − λ)  =  λ / [μ(μ − λ)]",
        "",
        "Relationship:              W  =  W<sub>q</sub> + 1/μ",
        "",
        "Prob. of n or more in system:  P(N ≥ n)  =  ρ<super>n</super>",
        "",
        "Prob. waiting time > t:   P(W<sub>q</sub> > t)  =  ρ · e<super>-(μ−λ)t</super>      t ≥ 0",
        "",
        "Prob. sojourn > t:        P(W > t)  =  e<super>-(μ−λ)t</super>              t ≥ 0",
    ], s))
    story.append(sp(2))

    story.append(section_header("3.3  Derivation of Key Formulas", s))
    story.append(sp())
    story.append(Paragraph(
        "<b>Step 1 — Birth-death parameters for M/M/1:</b> In every state n ≥ 1, arrival "
        "rate = λ, service rate = μ.  So λ<sub>n</sub> = λ and μ<sub>n</sub> = μ for all n ≥ 1, "
        "μ<sub>0</sub> = 0 (no departure when empty).", s['body']))
    story.append(Paragraph(
        "<b>Step 2 — Local balance equations:</b>", s['body_bold']))
    story.append(formula_box([
        "λ · P<sub>n</sub>  =  μ · P<sub>n+1</sub>     →     P<sub>n+1</sub>  =  (λ/μ) · P<sub>n</sub>  =  ρ · P<sub>n</sub>",
        "Applying recursively: P<sub>n</sub> = ρ<super>n</super> · P<sub>0</sub>",
    ], s))
    story.append(Paragraph(
        "<b>Step 3 — Normalisation:</b>", s['body_bold']))
    story.append(formula_box([
        "Σ<sub>n=0</sub><super>∞</super> P<sub>n</sub>  =  P<sub>0</sub> · Σ<sub>n=0</sub><super>∞</super> ρ<super>n</super>  =  P<sub>0</sub> / (1−ρ)  =  1",
        "→   P<sub>0</sub>  =  1 − ρ         (geometric series: Σρ<super>n</super> = 1/(1−ρ) for |ρ| < 1)",
    ], s))
    story.append(Paragraph(
        "<b>Step 4 — Derive L:</b>", s['body_bold']))
    story.append(formula_box([
        "L  =  Σ<sub>n=0</sub><super>∞</super> n · P<sub>n</sub>  =  (1−ρ) · Σ<sub>n=0</sub><super>∞</super> n · ρ<super>n</super>",
        "Using  Σ n·ρ<super>n</super> = ρ/(1−ρ)<super>2</super>   →   L  =  (1−ρ) · ρ/(1−ρ)<super>2</super>  =  ρ/(1−ρ)",
    ], s))
    story.append(Paragraph(
        "<b>Step 5 — Derive W, Lq, Wq via Little's Law:</b>", s['body_bold']))
    story.append(formula_box([
        "W   =  L / λ  =  [ρ/(1−ρ)] / λ  =  1/(μ−λ)",
        "W<sub>q</sub>  =  W − 1/μ  =  1/(μ−λ) − 1/μ  =  λ/[μ(μ−λ)]",
        "L<sub>q</sub>  =  λ · W<sub>q</sub>  =  λ<super>2</super>/[μ(μ−λ)]  =  ρ<super>2</super>/(1−ρ)",
    ], s))
    story.append(sp(2))

    story.append(section_header("3.4  State Probabilities and Distribution", s))
    story.append(sp())
    story.append(Paragraph(
        "The number of customers in the M/M/1 system in steady state follows a "
        "<b>geometric distribution</b>:", s['body']))
    story.append(formula_box([
        "P<sub>n</sub>  =  (1 − ρ) · ρ<super>n</super>          n = 0, 1, 2, …",
        "",
        "P(N ≥ k)  =  ρ<super>k</super>          (prob. of k or more customers in system)",
        "P(N > k)  =  ρ<super>k+1</super>",
        "P(N ≤ k)  =  1 − ρ<super>k+1</super>",
    ], s))
    story.append(sp(2))

    story.append(section_header("3.5  Solved Examples — M/M/1", s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 3.1 — Basic M/M/1 Performance Metrics",
        [
            "Problem: A server receives requests at rate λ = 4 requests/min. "
            "Service rate μ = 6 requests/min. Find: ρ, P0, L, Lq, W, Wq.",
            "",
            "Solution:",
            "ρ = λ/μ = 4/6 = 0.667   (stability check: 0.667 < 1 ✔)",
            "P0 = 1 − ρ = 1 − 0.667 = 0.333   (server idle 33.3% of time)",
            "L  = ρ/(1−ρ) = 0.667/0.333 = 2.00 customers",
            "Lq = ρ²/(1−ρ) = (0.667)²/0.333 = 0.4449/0.333 = 1.334 customers",
            "W  = 1/(μ−λ) = 1/(6−4) = 0.500 min",
            "Wq = λ/[μ(μ−λ)] = 4/[6×2] = 4/12 = 0.333 min",
            "",
            "Verification via Little's Law:",
            "L = λ·W = 4 × 0.5 = 2.00 ✔     Lq = λ·Wq = 4 × 0.333 = 1.333 ✔",
            "W = Wq + 1/μ = 0.333 + 1/6 = 0.333 + 0.167 = 0.500 ✔",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 3.2 — Probability Calculations",
        [
            "Problem (same system): Find (a) P(N≥3), (b) P(N=2), (c) P(Wq > 0.5 min).",
            "",
            "ρ = 0.667,  μ−λ = 2",
            "",
            "(a) P(N ≥ 3) = ρ³ = (0.667)³ = 0.2963  ≈ 29.6%",
            "",
            "(b) P(N = 2) = P(N≥2) − P(N≥3) = ρ² − ρ³ = (0.667)² − (0.667)³",
            "             = 0.4449 − 0.2963 = 0.1486  ≈ 14.9%",
            "  OR directly: P(N=2) = (1−ρ)·ρ² = 0.333 × 0.4449 = 0.1482 ✔",
            "",
            "(c) P(Wq > 0.5) = ρ · e^{−(μ−λ)·t} = 0.667 × e^{−2×0.5}",
            "                 = 0.667 × e^{−1} = 0.667 × 0.3679 = 0.2453  ≈ 24.5%",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 3.3 — Finding Parameters Given Performance Target",
        [
            "Problem: A system requires W ≤ 2 seconds. Arrival rate λ = 10/s. "
            "What minimum service rate μ is needed?",
            "",
            "Solution: W = 1/(μ−λ) ≤ 2",
            "1/(μ−10) ≤ 2  →  μ−10 ≥ 1/2  →  μ ≥ 10.5 requests/second",
            "",
            "Also check stability: ρ = λ/μ = 10/10.5 = 0.952 < 1 ✔",
            "",
            "At μ = 10.5:  W = 1/(10.5−10) = 1/0.5 = 2.0 s (exactly at target)",
            "Wq = W − 1/μ = 2.0 − 1/10.5 = 2.0 − 0.0952 = 1.905 s",
            "L  = λ·W = 10 × 2 = 20 customers  |  Lq = 10 × 1.905 = 19.05 customers",
        ], s))
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 4: M/M/c (Multi-Server)
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("4", "M/M/c QUEUE — MULTI-SERVER", s))
    story.append(sp(2))

    story.append(section_header("4.1  Model Assumptions", s))
    story.append(sp())
    for a in [
        "Poisson arrivals at rate λ.",
        "Exponential service times with rate μ per server.",
        "c parallel servers, each with the same service rate μ.",
        "Single shared queue: customers wait in one line and go to next available server.",
        "Infinite capacity (K = ∞), infinite population.",
        "Stability condition: ρ = λ/(cμ) < 1  (note: divide by c, not 1).",
        "Queue discipline: FCFS.",
    ]:
        story.append(Paragraph(f"• {a}", s['bullet']))
    story.append(sp())
    story.append(Paragraph(
        "<b>Birth-Death rates for M/M/c:</b> λ<sub>n</sub> = λ for all n. "
        "μ<sub>n</sub> = n·μ for n ≤ c (each of the n busy servers contributes μ), "
        "and μ<sub>n</sub> = c·μ for n > c (all c servers busy).", s['body']))
    story.append(sp(2))

    story.append(section_header("4.2  Erlang-C Formula (M/M/c Delay Probability)", s))
    story.append(sp())
    story.append(Paragraph(
        "The <b>Erlang-C formula</b>, also written C(c, λ/μ) or C(c, a) where a = λ/μ "
        "(offered load in Erlangs), gives the probability that an arriving customer "
        "<b>must wait</b> (all servers are busy):", s['body']))
    story.append(formula_box([
        "C(c, a)  =  Erlang-C  =",
        "",
        "     [ a<super>c</super>/(c! · (1 − ρ)) ]",
        "  ─────────────────────────────────────────",
        "  Σ<sub>k=0</sub><super>c−1</super> a<super>k</super>/k!  +  [ a<super>c</super>/(c! · (1 − ρ)) ]",
        "",
        "where  a = λ/μ  (total offered load),  ρ = a/c = λ/(c·μ)  (per-server utilisation)",
    ], s))
    story.append(sp(2))

    story.append(section_header("4.3  Complete M/M/c Formula Sheet", s))
    story.append(sp())
    story.append(formula_box([
        "Offered load:          a = λ/μ      (Erlangs)",
        "Per-server utilisation: ρ = a/c = λ/(c·μ)      (ρ < 1 for stability)",
        "",
        "P<sub>0</sub>  =  [ Σ<sub>k=0</sub><super>c−1</super> (a<super>k</super>/k!)  +  a<super>c</super>/(c! · (1−ρ)) ]<super>−1</super>",
        "",
        "P<sub>n</sub>  =  (a<super>n</super>/n!) · P<sub>0</sub>               for  0 ≤ n ≤ c",
        "P<sub>n</sub>  =  (a<super>n</super> / (c<super>n−c</super> · c!)) · P<sub>0</sub>   for  n > c",
        "",
        "Delay probability (Erlang-C):  C(c,a) = P(wait) = P(all servers busy)",
        "  =  [a<super>c</super>·P<sub>0</sub>] / [c! · (1 − ρ)]",
        "",
        "Mean queue length:   L<sub>q</sub>  =  C(c,a) · ρ / (1 − ρ)",
        "",
        "Mean waiting time:   W<sub>q</sub>  =  L<sub>q</sub> / λ  =  C(c,a) / (c·μ − λ)",
        "",
        "Mean time in system: W  =  W<sub>q</sub> + 1/μ",
        "",
        "Mean number in system: L  =  λ · W  =  L<sub>q</sub> + λ/μ  =  L<sub>q</sub> + a",
        "",
        "Prob. waiting > t:  P(W<sub>q</sub> > t)  =  C(c,a) · e<super>−(c·μ − λ)·t</super>     t ≥ 0",
    ], s))
    story.append(sp(2))

    story.append(section_header("4.4  M/M/2 Special Case Formulas", s))
    story.append(sp())
    story.append(Paragraph("For c = 2 servers, the formulas simplify as follows:", s['body']))
    story.append(formula_box([
        "a = λ/μ,    ρ = λ/(2μ) = a/2     [stability: ρ < 1 means a < 2]",
        "",
        "P<sub>0</sub>  =  (1 − ρ) / (1 + ρ)  =  (2μ − λ) / (2μ + λ)",
        "",
        "C(2, a)  =  2ρ<super>2</super> / (1 − ρ<super>2</super>)  ×  P<sub>0</sub>  =  2ρ<super>2</super> P<sub>0</sub> / (1 − ρ)(1 + ρ)",
        "",
        "Alternatively:  C(2, a) = a<super>2</super>·P<sub>0</sub> / (2!(1−ρ)) = a<super>2</super>·P<sub>0</sub> / (2(1−ρ))",
        "",
        "L<sub>q</sub>  =  C(2,a) · ρ / (1 − ρ)",
        "W<sub>q</sub>  =  L<sub>q</sub> / λ",
        "W   =  W<sub>q</sub> + 1/μ",
        "L   =  λ · W",
    ], s))
    story.append(sp(2))

    story.append(section_header("4.5  Solved Examples — M/M/c", s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 4.1 — M/M/2 Queue",
        [
            "Problem: λ = 5 customers/hour, μ = 4 customers/hour per server, c = 2 servers.",
            "Find P0, C(2,a), Lq, Wq, W, L.",
            "",
            "Step 1: Check stability.  a = λ/μ = 5/4 = 1.25 Erlangs",
            "  ρ = a/c = 1.25/2 = 0.625 < 1 ✔",
            "",
            "Step 2: P0.  Using the M/M/c formula:",
            "  Σ(k=0 to 1) a^k/k! = a^0/0! + a^1/1! = 1 + 1.25 = 2.25",
            "  Last term = a^c / (c!(1−ρ)) = (1.25)^2 / (2! × (1−0.625))",
            "            = 1.5625 / (2 × 0.375) = 1.5625 / 0.75 = 2.0833",
            "  P0 = 1/(2.25 + 2.0833) = 1/4.3333 = 0.2308",
            "",
            "Step 3: Erlang-C (delay probability).",
            "  C(2, 1.25) = 2.0833 × P0 = 2.0833 × 0.2308 = 0.4808 ≈ 48.1%",
            "  (About 48% of customers must wait for a server.)",
            "",
            "Step 4: Queue metrics.",
            "  Lq = C(2,a) × ρ / (1−ρ) = 0.4808 × 0.625 / 0.375",
            "     = 0.3005 / 0.375 = 0.8013 customers",
            "  Wq = Lq / λ = 0.8013 / 5 = 0.1603 hours = 9.62 minutes",
            "  W  = Wq + 1/μ = 0.1603 + 0.25 = 0.4103 hours = 24.6 minutes",
            "  L  = λ·W = 5 × 0.4103 = 2.05 customers",
            "",
            "Verification: L = Lq + a = 0.8013 + 1.25 = 2.051 ✔",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 4.2 — Comparing Single Server vs Two Servers",
        [
            "Problem: λ = 8/hr, μ = 10/hr. Compare M/M/1 vs M/M/2 (each server at 10/hr).",
            "",
            "M/M/1: ρ = 8/10 = 0.8",
            "  L  = 0.8/(1−0.8) = 4.0  |  W = 1/(10−8) = 0.5 hr = 30 min",
            "  Lq = 0.8²/0.2 = 3.2     |  Wq = 0.8/(10−8)/1 = 8/(10×2) = 0.4 hr = 24 min",
            "",
            "M/M/2: a = 8/10 = 0.8,  ρ = 0.8/2 = 0.4",
            "  Σ(k=0,1) 0.8^k/k! = 1 + 0.8 = 1.8",
            "  Last term = (0.8)²/(2!(1−0.4)) = 0.64/(2×0.6) = 0.64/1.2 = 0.5333",
            "  P0 = 1/(1.8 + 0.5333) = 1/2.3333 = 0.4286",
            "  C(2, 0.8) = 0.5333 × 0.4286 = 0.2286",
            "  Lq = 0.2286 × 0.4/(1−0.4) = 0.2286 × 0.667 = 0.1524",
            "  Wq = 0.1524/8 = 0.01905 hr = 1.14 min",
            "  W  = 0.01905 + 0.1 = 0.119 hr = 7.14 min",
            "  L  = 8 × 0.119 = 0.952 customers",
            "",
            "Conclusion: Adding one server reduces Wq from 24 min to 1.14 min — a 21× improvement!",
            "This illustrates the dramatic benefit of pooled servers.",
        ], s))
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 5: M/G/1
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("5", "M/G/1 QUEUE — GENERAL SERVICE TIMES", s))
    story.append(sp(2))

    story.append(section_header("5.1  Model Assumptions", s))
    story.append(sp())
    for a in [
        "Arrivals: Poisson process with rate λ (inter-arrival ~ Exponential(λ)).",
        "Service: Any general distribution with mean E[S] = 1/μ and variance Var[S] = σ².",
        "Single server (c = 1).",
        "Infinite capacity, infinite population, FCFS.",
        "Stability: ρ = λ·E[S] = λ/μ < 1.",
        "Service times are iid and independent of arrivals.",
        "Note: Service times need NOT be exponential. This is the key generalisation over M/M/1.",
    ]:
        story.append(Paragraph(f"• {a}", s['bullet']))
    story.append(sp())
    story.append(Paragraph(
        "<b>Key statistic — Coefficient of Variation of Service Time:</b>", s['body_bold']))
    story.append(formula_box([
        "C<sub>s</sub><super>2</super>  =  Var[S] / (E[S])<super>2</super>  =  σ<super>2</super> / (1/μ)<super>2</super>  =  σ<super>2</super>μ<super>2</super>",
        "",
        "C<sub>s</sub><super>2</super> = 0  → Deterministic service (M/D/1 special case)",
        "C<sub>s</sub><super>2</super> = 1  → Exponential service (reduces to M/M/1)",
        "C<sub>s</sub><super>2</super> > 1  → High variability (e.g. hyperexponential)",
    ], s))
    story.append(sp(2))

    story.append(section_header("5.2  Pollaczek-Khinchine (P-K) Mean Value Formula", s))
    story.append(sp())
    story.append(Paragraph(
        "The <b>P-K formula</b> (Pollaczek 1930, Khinchine 1932) gives exact closed-form "
        "expressions for M/G/1 performance in terms of only the mean and variance of the "
        "service time:", s['body']))
    story.append(formula_box([
        "─────── P-K (Pollaczek-Khinchine) Mean Value Equations ───────",
        "",
        "Traffic intensity:   ρ  =  λ · E[S]  =  λ / μ",
        "",
        "E[S<super>2</super>] = second moment of service time = Var[S] + (E[S])<super>2</super> = σ<super>2</super> + 1/μ<super>2</super>",
        "",
        "Mean queue length:   L<sub>q</sub>  =  ρ<super>2</super> + λ<super>2</super>·Var[S]",
        "                            ──────────────────────",
        "                                   2(1 − ρ)",
        "",
        "Equivalently:        L<sub>q</sub>  =  ρ<super>2</super>(1 + C<sub>s</sub><super>2</super>) / [ 2(1 − ρ) ]",
        "",
        "Mean waiting time:   W<sub>q</sub>  =  L<sub>q</sub> / λ  =  λ·E[S<super>2</super>] / [ 2(1 − ρ) ]",
        "",
        "Mean time in system: W  =  W<sub>q</sub> + E[S]  =  W<sub>q</sub> + 1/μ",
        "",
        "Mean number in system: L  =  λ · W  =  L<sub>q</sub> + ρ",
        "",
        "Idle probability:    P<sub>0</sub>  =  1 − ρ  (same as M/M/1!)",
    ], s))
    story.append(sp(2))
    story.append(note_box(
        "KEY INSIGHT: The M/G/1 formulas depend on the service distribution <b>only through "
        "its first two moments</b> E[S] and E[S²] (equivalently, mean and variance). "
        "Higher moments do not affect mean performance metrics. "
        "This is known as the P-K mean value result.", s))
    story.append(sp(2))

    story.append(section_header("5.3  M/D/1 Special Case (Deterministic Service)", s))
    story.append(sp())
    story.append(Paragraph(
        "When service time is constant (deterministic) D = 1/μ: Var[S] = 0, C²<sub>s</sub> = 0.",
        s['body']))
    story.append(formula_box([
        "M/D/1:   L<sub>q</sub>  =  ρ<super>2</super> / [ 2(1 − ρ) ]",
        "         W<sub>q</sub>  =  ρ / [ 2μ(1 − ρ) ]",
        "",
        "Note:  L<sub>q</sub>(M/D/1) = (1/2) × L<sub>q</sub>(M/M/1)",
        "Deterministic service achieves exactly HALF the queue length of exponential service!",
    ], s))
    story.append(sp(2))

    story.append(section_header("5.4  Decomposition Property of M/G/1", s))
    story.append(sp())
    story.append(Paragraph(
        "The P-K formula can be interpreted via the <b>decomposition</b>:", s['body']))
    story.append(formula_box([
        "L<sub>q</sub>(M/G/1)  =  L<sub>q</sub>(M/M/1) × (1 + C<sub>s</sub><super>2</super>) / 2",
        "",
        "When C<sub>s</sub><super>2</super> = 1 (exponential): L<sub>q</sub>(M/G/1) = L<sub>q</sub>(M/M/1) ✔",
        "When C<sub>s</sub><super>2</super> = 0 (deterministic): L<sub>q</sub>(M/G/1) = (1/2)·L<sub>q</sub>(M/M/1) ✔",
        "When C<sub>s</sub><super>2</super> = 2 (hyperexponential): L<sub>q</sub>(M/G/1) = 1.5 × L<sub>q</sub>(M/M/1)",
    ], s))
    story.append(sp(2))

    story.append(section_header("5.5  Solved Examples — M/G/1", s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 5.1 — M/G/1 with Given Mean and Variance",
        [
            "Problem: λ = 2 jobs/sec. Service: E[S] = 0.4 sec, Var[S] = 0.2 sec².",
            "Find Lq, Wq, W, L.",
            "",
            "Step 1: ρ = λ·E[S] = 2 × 0.4 = 0.8   (stability: 0.8 < 1 ✔)",
            "",
            "Step 2: E[S²] = Var[S] + (E[S])² = 0.2 + (0.4)² = 0.2 + 0.16 = 0.36 sec²",
            "",
            "Step 3: Lq = λ²·Var[S] + ρ²    =  (4)(0.2) + (0.64)",
            "              ─────────────────       ──────────────────",
            "                 2(1 − ρ)                  2(0.2)",
            "           = (0.8 + 0.64)/0.4 = 1.44/0.4 = 3.6 customers",
            "",
            "  [Alternatively: Wq = λ·E[S²]/(2(1−ρ)) = 2×0.36/(2×0.2) = 0.72/0.4 = 1.8 sec]",
            "",
            "Step 4: Wq = Lq/λ = 3.6/2 = 1.8 sec   (matches above ✔)",
            "        W  = Wq + E[S] = 1.8 + 0.4 = 2.2 sec",
            "        L  = λ·W = 2 × 2.2 = 4.4 customers",
            "",
            "Check: L = Lq + ρ = 3.6 + 0.8 = 4.4 ✔",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 5.2 — M/D/1 vs M/M/1 Comparison",
        [
            "Problem: λ = 3/min, μ = 5/min.  Compare M/M/1 vs M/D/1 queue lengths.",
            "",
            "Common: ρ = 3/5 = 0.6,   1−ρ = 0.4",
            "",
            "M/M/1: Lq = ρ²/(1−ρ) = 0.36/0.4 = 0.9 customers",
            "",
            "M/D/1: Var[S] = 0, E[S] = 1/5 = 0.2 min, E[S²] = 0 + 0.04 = 0.04",
            "  Lq = λ²·0 + ρ²  =  0 + 0.36  = 0.36  = 0.45 customers",
            "        ──────────    ──────────",
            "          2(1−ρ)       0.8",
            "",
            "Reduction: (0.9 − 0.45)/0.9 = 50% reduction in queue by using deterministic service!",
            "",
            "M/D/1 Wq = 0.45/3 = 0.15 min   vs  M/M/1 Wq = 0.9/3 = 0.3 min",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 5.3 — M/G/1 with Erlang-2 Service",
        [
            "Problem: λ = 4/hr. Service times follow Erlang-2 distribution with mean E[S] = 0.2 hr.",
            "For Erlang-k distribution: Var[S] = E[S]²/k = (0.2)²/2 = 0.02 hr².",
            "Find Lq, Wq.",
            "",
            "ρ = 4 × 0.2 = 0.8",
            "E[S²] = Var[S] + (E[S])² = 0.02 + 0.04 = 0.06 hr²",
            "C²s   = Var[S]/(E[S])² = 0.02/0.04 = 0.5",
            "",
            "Wq = λ·E[S²] / (2(1−ρ)) = 4 × 0.06 / (2 × 0.2) = 0.24/0.4 = 0.6 hr",
            "Lq = λ·Wq = 4 × 0.6 = 2.4 customers",
            "",
            "Compare with M/M/1 (C²s = 1): Lq(MM1) = 0.8²/0.2 = 3.2",
            "Erlang-2 gives (1+0.5)/2 = 0.75 × Lq(MM1) = 0.75 × 3.2 = 2.4 ✔",
        ], s))
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 6: G/G/1
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("6", "G/G/1 QUEUE — GENERAL ARRIVALS AND SERVICE", s))
    story.append(sp(2))

    story.append(section_header("6.1  Model Assumptions", s))
    story.append(sp())
    for a in [
        "Arrivals: ANY general inter-arrival time distribution with mean 1/λ and variance σ²_a (C²_a = σ²_a · λ²).",
        "Service: ANY general service time distribution with mean E[S] = 1/μ and variance σ²_s (C²_s = σ²_s · μ²).",
        "Single server.",
        "Stability: ρ = λ/μ < 1.",
        "No closed-form exact solution exists in general for G/G/1.",
        "We use bounds and the Kingman (VUT) approximation.",
    ]:
        story.append(Paragraph(f"• {a}", s['bullet']))
    story.append(sp(2))

    story.append(section_header("6.2  Kingman's Approximation (VUT Formula)", s))
    story.append(sp())
    story.append(Paragraph(
        "John Kingman (1961) derived a famous approximation for the mean waiting time in "
        "G/G/1 queues. It is also called the <b>VUT equation</b> (Variability × Utilisation × Service Time):",
        s['body']))
    story.append(formula_box([
        "─────── Kingman's VUT Approximation (G/G/1) ───────",
        "",
        "W<sub>q</sub>  ≈  (C<sub>a</sub><super>2</super> + C<sub>s</sub><super>2</super>)/2  ×  ρ/(1−ρ)  ×  E[S]",
        "",
        "where:",
        "  C<sub>a</sub><super>2</super>  =  Var[A] / (E[A])<super>2</super>  =  σ<sub>a</sub><super>2</super> · λ<super>2</super>   (squared coefficient of variation of inter-arrival time)",
        "  C<sub>s</sub><super>2</super>  =  Var[S] / (E[S])<super>2</super>  =  σ<sub>s</sub><super>2</super> · μ<super>2</super>   (squared coefficient of variation of service time)",
        "  ρ  =  λ · E[S]  =  λ/μ                                      (server utilisation)",
        "  E[S]  =  1/μ                                                  (mean service time)",
        "",
        "L<sub>q</sub>  ≈  λ · W<sub>q</sub>",
        "W   ≈  W<sub>q</sub> + E[S]",
        "L   ≈  λ · W",
    ], s))
    story.append(sp())
    story.append(note_box(
        "Special cases of Kingman's formula: "
        "(1) C²a = 1, C²s = 1 → Wq = ρ/((1−ρ)·μ) = M/M/1 exact result. "
        "(2) C²a = 1, C²s = 0 → Wq = ρ/(2(1−ρ)·μ) = M/D/1 exact result. "
        "(3) C²a = 0 (deterministic arrivals) → halves the variability term.", s))
    story.append(sp(2))

    story.append(section_header("6.3  Bounds for G/G/1", s))
    story.append(sp())
    story.append(Paragraph("<b>Kleinrock Lower Bound:</b>", s['body_bold']))
    story.append(formula_box([
        "W<sub>q</sub>  ≥  ρ · E[S] / (1 − ρ)  ×  max(C<sub>a</sub><super>2</super>, C<sub>s</sub><super>2</super> − 1) / 2",
        "(for general G/G/1 — not always tight)",
    ], s))
    story.append(sp())
    story.append(Paragraph("<b>Heavy Traffic Bound (ρ → 1):</b>", s['body_bold']))
    story.append(formula_box([
        "As ρ → 1:   W<sub>q</sub>  →  (C<sub>a</sub><super>2</super> + C<sub>s</sub><super>2</super>) / (2μ(1 − ρ))",
        "(Kingman's formula becomes exact in heavy traffic)",
    ], s))
    story.append(sp(2))

    story.append(section_header("6.4  Solved Examples — G/G/1", s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 6.1 — G/G/1 via Kingman Approximation",
        [
            "Problem: Arrivals: mean inter-arrival = 1/λ = 5 min, σ_a = 4 min.",
            "Service: mean E[S] = 4 min, σ_s = 3 min.",
            "Find approximate Wq, Lq, W, L.",
            "",
            "Step 1: Parameters.",
            "  λ = 1/5 = 0.2/min,   μ = 1/4 = 0.25/min",
            "  ρ = λ/μ = 0.2/0.25 = 0.8   (stable ✔)",
            "",
            "Step 2: Coefficients of variation.",
            "  C²a = σ²a × λ² = (4)² × (0.2)² = 16 × 0.04 = 0.64",
            "  C²s = σ²s × μ² = (3)² × (0.25)² = 9 × 0.0625 = 0.5625",
            "",
            "Step 3: Kingman's formula.",
            "  Wq ≈ (C²a + C²s)/2 × ρ/(1−ρ) × E[S]",
            "     = (0.64 + 0.5625)/2 × (0.8/0.2) × 4",
            "     = (1.2025/2) × 4 × 4",
            "     = 0.60125 × 4 × 4 = 9.62 min",
            "",
            "Step 4: Remaining metrics.",
            "  Lq = λ·Wq = 0.2 × 9.62 = 1.924 customers",
            "  W  = Wq + E[S] = 9.62 + 4 = 13.62 min",
            "  L  = λ·W = 0.2 × 13.62 = 2.724 customers",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 6.2 — Impact of Variability on G/G/1",
        [
            "Problem: ρ = 0.8, E[S] = 1 min. Compare three scenarios:",
            "  (A) C²a = 1, C²s = 1  (M/M/1)",
            "  (B) C²a = 1, C²s = 0  (M/D/1)",
            "  (C) C²a = 2, C²s = 2  (High variability)",
            "",
            "Common factor: ρ/(1−ρ) × E[S] = 0.8/0.2 × 1 = 4 min",
            "",
            "(A) Wq ≈ (1+1)/2 × 4 = 4.0 min   [exact M/M/1: ρ/(μ−λ) = 0.8/0.2 = 4 ✔]",
            "(B) Wq ≈ (1+0)/2 × 4 = 2.0 min   [exact M/D/1: same]",
            "(C) Wq ≈ (2+2)/2 × 4 = 8.0 min   [2× worse than M/M/1!]",
            "",
            "Lesson: Doubling variability (C²s from 1 to 2) doubles the waiting time.",
            "Reducing variability is as effective as reducing load for improving performance.",
        ], s))
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 7: SIMULATION
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("7", "SIMULATION OF M/M/1 AND M/M/2 QUEUES", s))
    story.append(sp(2))

    story.append(section_header("7.1  Why Simulate?", s))
    story.append(sp())
    story.append(Paragraph(
        "While M/M/1 and M/M/2 have closed-form analytical solutions, simulation is "
        "essential when:", s['body']))
    for r in [
        "The system is too complex for analytical treatment (non-Markovian, time-varying rates, network of queues).",
        "We want to verify the analytical formulas against a computational model.",
        "The system has finite buffers, complex routing, breakdowns, or priority classes.",
        "We want transient (time-dependent) behaviour, not just steady-state.",
    ]:
        story.append(Paragraph(f"• {r}", s['bullet']))
    story.append(sp(2))

    story.append(section_header("7.2  Event-Driven (Discrete-Event) Simulation", s))
    story.append(sp())
    story.append(Paragraph(
        "In <b>discrete-event simulation (DES)</b> the system state changes only at event "
        "times. Between events the state is constant. The two event types for a single-queue "
        "system are <b>ARRIVAL</b> and <b>DEPARTURE</b>.", s['body']))
    story.append(Paragraph("<b>Global Variables:</b>", s['body_bold']))
    for v in [
        "Clock t — current simulation time.",
        "N(t) — number of customers in system at time t.",
        "Event list (Future Event List, FEL) — sorted list of (event_time, event_type).",
        "Accumulators — total busy time, total wait times, counts for statistics.",
    ]:
        story.append(Paragraph(f"• {v}", s['bullet']))
    story.append(sp())
    story.append(Paragraph("<b>Main Simulation Loop:</b>", s['body_bold']))
    steps_sim = [
        ("Initialise", "Set t = 0, N = 0. Schedule first arrival at t_A = −ln(U)/λ."),
        ("Advance clock", "Remove the earliest event from FEL; set t = event_time."),
        ("Process Arrival event",
            "N++. If N = 1 (server was idle): schedule departure at t + S (S ~ Exp(μ)). "
            "Record arrival time for this customer."),
        ("Process Departure event",
            "Record sojourn time = t − arrival_time. N−−. If N > 0: start serving next "
            "customer (schedule departure at t + S). If N = 0: server goes idle."),
        ("Schedule next arrival",
            "After processing any arrival: generate next inter-arrival A ~ Exp(λ); "
            "schedule arrival at t + A."),
        ("Repeat", "Go to step 2 until stopping criterion (fixed time T or fixed number of customers)."),
        ("Collect statistics", "Compute sample means for W, Wq, L, Lq by time-averaging."),
    ]
    for i, (name, desc) in enumerate(steps_sim, 1):
        story.append(Paragraph(f"<b>{i}. {name}:</b> {desc}", s['bullet']))
    story.append(sp(2))

    story.append(section_header("7.3  Random Variate Generation", s))
    story.append(sp())
    story.append(Paragraph(
        "To generate exponential random variates from U ~ Uniform(0,1):", s['body']))
    story.append(formula_box([
        "Inverse Transform Method:",
        "",
        "If U ~ Uniform(0,1), then  X = −(1/λ) · ln(U)  ~  Exponential(λ)",
        "",
        "For inter-arrival times:  A = −(1/λ) · ln(U<sub>1</sub>)",
        "For service times:        S = −(1/μ) · ln(U<sub>2</sub>)",
        "",
        "(Use separate independent U values for arrivals and services)",
    ], s))
    story.append(sp(2))

    story.append(section_header("7.4  Step-by-Step Hand Simulation — M/M/1", s))
    story.append(sp())
    story.append(Paragraph(
        "<b>Given:</b> λ = 2/min, μ = 3/min (ρ = 2/3 = 0.667). Simulate first 5 customers.",
        s['body']))
    story.append(Paragraph(
        "Use the following pre-generated uniform random numbers:", s['body']))
    story.append(Paragraph(
        "Arrivals U: 0.25, 0.60, 0.45, 0.80, 0.10   "
        "→ A = −(1/2)·ln(U)",
        s['body']))
    story.append(Paragraph(
        "Service U: 0.70, 0.30, 0.55, 0.90, 0.20    "
        "→ S = −(1/3)·ln(U)",
        s['body']))
    story.append(sp())
    story.append(Paragraph("<b>Compute inter-arrival times A and service times S:</b>", s['body_bold']))
    rng_headers = ["Customer", "U_arr", "A = -(1/2)ln(U)", "Arrival time", "U_svc", "S = -(1/3)ln(U)"]
    rng_rows = [
        ["1", "0.25", "0.693 min", "0.693", "0.70", "0.119 min"],
        ["2", "0.60", "0.255 min", "0.948", "0.30", "0.401 min"],
        ["3", "0.45", "0.398 min", "1.346", "0.55", "0.194 min"],
        ["4", "0.80", "0.112 min", "1.458", "0.90", "0.035 min"],
        ["5", "0.10", "1.151 min", "2.609", "0.20", "0.537 min"],
    ]
    story.append(two_col_table(rng_headers, rng_rows, s,
        col_widths=[2*cm, 2*cm, 3.5*cm, 3*cm, 2*cm, 3.5*cm]))
    story.append(sp())
    story.append(Paragraph("<b>Simulation trace (event-by-event):</b>", s['body_bold']))
    trace_headers = ["Event", "Time t", "N(t)", "Server Busy Until", "Wq", "W"]
    trace_rows = [
        ["Arrive C1", "0.693", "1", "0.693+0.119=0.812", "0.000", "0.119"],
        ["Depart C1", "0.812", "0", "—", "—", "—"],
        ["Arrive C2", "0.948", "1", "0.948+0.401=1.349", "0.000", "0.401"],
        ["Arrive C3", "1.346", "2", "1.349 (busy)", "0.003", "0.197"],
        ["Depart C2", "1.349", "1", "1.349+0.194=1.543", "—", "—"],
        ["Arrive C4", "1.458", "2", "1.543 (busy)", "0.085", "0.120"],
        ["Depart C3", "1.543", "1", "1.543+0.035=1.578", "—", "—"],
        ["Depart C4", "1.578", "0", "—", "—", "—"],
        ["Arrive C5", "2.609", "1", "2.609+0.537=3.146", "0.000", "0.537"],
    ]
    story.append(two_col_table(trace_headers, trace_rows, s,
        col_widths=[2.8*cm, 2*cm, 1.8*cm, 4.5*cm, 2*cm, 2*cm]))
    story.append(sp())
    story.append(Paragraph(
        "<b>Sample statistics from 5 customers:</b> "
        "Average Wq = (0+0+0.003+0.085+0)/5 = 0.0176 min &nbsp; "
        "Average W = (0.119+0.401+0.197+0.120+0.537)/5 = 0.275 min &nbsp;"
        "(Analytical: Wq = 0.333 min, W = 0.5 min — simulation converges with more customers)", s['body']))
    story.append(sp(2))

    story.append(section_header("7.5  Step-by-Step Hand Simulation — M/M/2", s))
    story.append(sp())
    story.append(Paragraph(
        "<b>Given:</b> λ = 3/min, μ = 2/min per server, c = 2 servers (ρ = 3/(2×2) = 0.75).",
        s['body']))
    story.append(Paragraph(
        "For M/M/2, maintain state for each server separately. "
        "An arriving customer goes to any idle server (Server 1 first by convention); "
        "if both busy, joins the queue.", s['body']))
    story.append(sp())
    story.append(Paragraph("<b>Key differences from M/M/1 simulation:</b>", s['body_bold']))
    story.append(Paragraph("• Track two server states: S1_busy_until and S2_busy_until.", s['bullet']))
    story.append(Paragraph("• On arrival: assign to first idle server (min(S1_free, S2_free) ≤ t).", s['bullet']))
    story.append(Paragraph("• If both busy: add to queue; assign on next departure.", s['bullet']))
    story.append(Paragraph("• On departure: if queue non-empty, immediately assign waiting customer to freed server.", s['bullet']))
    story.append(sp())
    story.append(Paragraph(
        "Pre-generated values (λ=3, μ=2): Use A<sub>i</sub> = −(1/3)ln(U_a), S<sub>i</sub> = −(1/2)ln(U_s).",
        s['body']))
    rng2_headers = ["Cust", "U_arr", "A (min)", "Arr. Time", "U_svc", "S (min)"]
    rng2_rows = [
        ["1", "0.40", "0.306", "0.306", "0.85", "0.081"],
        ["2", "0.70", "0.119", "0.425", "0.25", "0.693"],
        ["3", "0.20", "0.537", "0.962", "0.60", "0.255"],
        ["4", "0.55", "0.199", "1.161", "0.45", "0.398"],
        ["5", "0.90", "0.035", "1.196", "0.80", "0.112"],
    ]
    story.append(two_col_table(rng2_headers, rng2_rows, s,
        col_widths=[1.8*cm, 2*cm, 2*cm, 2.5*cm, 2*cm, 2*cm]))
    story.append(sp())
    mm2_trace_headers = ["Event", "t", "N", "S1 free", "S2 free", "Assigned to", "Wq"]
    mm2_trace_rows = [
        ["Arrive C1", "0.306", "1", "0.306+0.081=0.387", "idle", "S1", "0"],
        ["Arrive C2", "0.425", "2", "0.387 (busy)", "0.425+0.693=1.118", "S2", "0"],
        ["Depart C1", "0.387", "1", "idle", "1.118 (busy)", "—", "—"],
        ["Arrive C3", "0.962", "2", "0.962+0.255=1.217", "1.118 (busy)", "S1", "0"],
        ["Arrive C4", "1.161", "3", "1.217 (busy)", "1.118 (busy)", "queue", "0.056*"],
        ["Depart S2 C2", "1.118", "2→C4 starts", "1.217", "1.118+0.398=1.516", "S2 (C4)", "0.056"],
        ["Arrive C5", "1.196", "3", "1.217 (busy)", "1.516 (busy)", "queue", "wait"],
        ["Depart S1 C3", "1.217", "C5 starts", "1.217+0.112=1.329", "1.516", "S1 (C5)", "0.021"],
    ]
    story.append(two_col_table(mm2_trace_headers, mm2_trace_rows, s,
        col_widths=[2.8*cm, 1.5*cm, 2.5*cm, 2.5*cm, 2.5*cm, 2.5*cm, 1.5*cm]))
    story.append(sp())
    story.append(Paragraph(
        "<b>C4 Wq:</b> C4 arrived at 1.161, S2 freed at 1.118 → Wq = 1.118 − 1.161 < 0? "
        "No — C4 arrived at 1.161 and both servers busy; S2 freed at 1.118 which is before "
        "C4's arrival, so C4 actually finds S2 free! Let us redo: at t=1.161 check servers: "
        "S1 free until 1.217 > 1.161 (busy), S2 free until 1.118 < 1.161 (idle). "
        "So C4 is assigned directly to S2 with Wq = 0. "
        "C5 arrives at 1.196: S1 busy (1.217), S2 busy (1.516) → waits. "
        "S1 frees at 1.217: C5 starts service → Wq(C5) = 1.217 − 1.196 = 0.021 min.", s['body']))
    story.append(sp(2))

    story.append(section_header("7.6  Performance Estimation from Simulation", s))
    story.append(sp())
    story.append(Paragraph("<b>Time-Average Statistics:</b>", s['body_bold']))
    story.append(formula_box([
        "L  =  (1/T) × ∫<sub>0</sub><super>T</super> N(t) dt  =  (1/T) × Σ<sub>i</sub> n<sub>i</sub> · Δt<sub>i</sub>",
        "(weighted sum: each state n<sub>i</sub> weighted by time spent in that state)",
        "",
        "W  =  (1/C) × Σ<sub>j=1</sub><super>C</super> W<sub>j</sub>   (average over C completed customers)",
        "",
        "Verification: L = λ × W   (Little's Law must hold in simulation output too)",
    ], s))
    story.append(sp())
    story.append(Paragraph("<b>Simulation Output Analysis:</b>", s['body_bold']))
    for p in [
        "Warm-up period: Discard initial transient observations (system starts empty but steady state is different).",
        "Run length: Use sufficiently long simulation to reduce estimation error.",
        "Replication: Run multiple independent replications and compute confidence intervals.",
        "Confidence interval for mean W: W̄ ± t_{α/2, n-1} · (s/√n) where s = sample std dev, n = replications.",
    ]:
        story.append(Paragraph(f"• {p}", s['bullet']))
    story.append(PageBreak())

    # ════════════════════════════════════════════════════════════════════════
    # CHAPTER 8: SUMMARY AND EXAM TIPS
    # ════════════════════════════════════════════════════════════════════════
    story.append(chapter_banner("8", "COMPARATIVE SUMMARY AND EXAM TIPS", s))
    story.append(sp(2))

    story.append(section_header("8.1  Model Comparison Table", s))
    story.append(sp())
    comp_headers = ["Feature", "M/M/1", "M/M/c", "M/G/1", "G/G/1"]
    comp_rows = [
        ["Arrivals", "Poisson (λ)", "Poisson (λ)", "Poisson (λ)", "General (λ, σ²_a)"],
        ["Service", "Exponential (μ)", "Exponential (μ/server)", "General (E[S], Var[S])", "General (E[S], Var[S])"],
        ["Servers", "1", "c ≥ 1", "1", "1"],
        ["Exact solution?", "Yes", "Yes", "Yes (P-K)", "No (approx only)"],
        ["Key formula", "L=ρ/(1−ρ)", "Erlang-C + Lq", "P-K formula", "Kingman VUT"],
        ["P0", "1−ρ", "Complex (Σ series)", "1−ρ", "≈ 1−ρ"],
        ["Stability", "ρ = λ/μ < 1", "ρ = λ/(cμ) < 1", "ρ = λ/μ < 1", "ρ = λ/μ < 1"],
        ["Service variability effect", "Fixed (Exp)", "Fixed (Exp)", "Explicit via C²s", "Explicit via C²a, C²s"],
        ["Reduces to M/M/1?", "—", "Yes (c=1)", "Yes (C²s=1)", "Yes (C²a=C²s=1)"],
    ]
    story.append(two_col_table(comp_headers, comp_rows, s,
        col_widths=[3.5*cm, 3.2*cm, 3.2*cm, 3.2*cm, 3.2*cm]))
    story.append(sp(2))

    story.append(section_header("8.2  Master Formula Quick-Reference Sheet", s))
    story.append(sp())

    story.append(Paragraph("<b>M/M/1</b>", s['h3']))
    story.append(formula_box([
        "ρ=λ/μ   P0=1−ρ   Pn=(1−ρ)ρⁿ   L=ρ/(1−ρ)   Lq=ρ²/(1−ρ)   W=1/(μ−λ)   Wq=ρ/(μ−λ)/1   =λ/[μ(μ−λ)]",
    ], s))
    story.append(sp())

    story.append(Paragraph("<b>M/M/c</b>", s['h3']))
    story.append(formula_box([
        "a=λ/μ   ρ=a/c   P0=[Σ(k=0→c-1) aᵏ/k!  +  aᶜ/(c!(1−ρ))]⁻¹",
        "C(c,a)=[aᶜ·P0]/[c!(1−ρ)]   Lq=C(c,a)·ρ/(1−ρ)   Wq=Lq/λ   W=Wq+1/μ   L=λW",
    ], s))
    story.append(sp())

    story.append(Paragraph("<b>M/G/1 (P-K)</b>", s['h3']))
    story.append(formula_box([
        "ρ=λ/μ   E[S²]=Var[S]+(E[S])²   Lq=(ρ²+λ²Var[S])/(2(1−ρ))=ρ²(1+C²s)/(2(1−ρ))",
        "Wq=λE[S²]/(2(1−ρ))   W=Wq+E[S]   L=λW   P0=1−ρ",
    ], s))
    story.append(sp())

    story.append(Paragraph("<b>G/G/1 (Kingman)</b>", s['h3']))
    story.append(formula_box([
        "Wq ≈ (C²a+C²s)/2 × ρ/(1−ρ) × E[S]   Lq=λWq   W=Wq+E[S]   L=λW",
    ], s))
    story.append(sp())

    story.append(Paragraph("<b>Little's Law (Universal)</b>", s['h3']))
    story.append(formula_box([
        "L = λ·W     Lq = λ·Wq     W = Wq + E[S]     L = Lq + ρ (single server)",
    ], s))
    story.append(sp(2))

    story.append(section_header("8.3  Common Exam Question Types", s))
    story.append(sp())
    qtypes = [
        ("Type 1: Calculate all metrics",
            "Given λ, μ (and c for multi-server): compute ρ, P0, L, Lq, W, Wq. "
            "Method: identify model → plug into formulas → verify with Little's Law."),
        ("Type 2: Given one metric, find another",
            "e.g. 'Average queue length is 5, arrival rate is 2/min, find W.' "
            "Use L = λW → W = 5/2 = 2.5 min. Then Wq = W − 1/μ, Lq = λWq."),
        ("Type 3: Find parameter for target performance",
            "e.g. 'Find μ such that W ≤ T.' Set up inequality W = 1/(μ−λ) ≤ T, solve for μ. "
            "Always verify stability afterwards."),
        ("Type 4: Compare models",
            "Calculate metrics for M/M/1 and M/M/2 side-by-side. "
            "Comment on trade-off between cost (extra server) and benefit (reduced wait)."),
        ("Type 5: M/G/1 with given moments",
            "Given E[S] and σ²: compute ρ = λ·E[S], E[S²], then apply P-K formula."),
        ("Type 6: Simulation trace",
            "Given U values: generate A and S using inverse transform, trace event sequence, "
            "compute sample Wq and W, compare with theoretical values."),
        ("Type 7: Stability and feasibility",
            "Check ρ < 1. If ρ ≥ 1: state system is unstable (queue → ∞), no steady-state exists."),
        ("Type 8: G/G/1 Kingman approximation",
            "Given σ²_a and σ²_s: compute C²a, C²s, apply Kingman. "
            "Discuss effect of variability."),
    ]
    for qtype, method in qtypes:
        story.append(Paragraph(f"<b>{qtype}:</b> {method}", s['bullet']))
        story.append(sp())
    story.append(sp())

    story.append(section_header("8.4  Key Relationships, Pitfalls and Tricks", s))
    story.append(sp())
    story.append(Paragraph("<b>MUST-KNOW Relationships:</b>", s['body_bold']))
    story.append(formula_box([
        "L  =  Lq  +  ρ                   (for single server: ρ = mean # in service)",
        "L  =  Lq  +  λ/μ  =  Lq + a     (for multi-server: a = λ/μ = mean # in service)",
        "W  =  Wq  +  1/μ  =  Wq + E[S]",
        "P(server busy) = ρ   =   1 − P0   (for M/M/1 and M/G/1)",
        "For M/G/1: Lq(C²s) = Lq(MM1) × (1+C²s)/2",
        "For G/G/1: Wq(Kingman) = Wq(MM1) × (C²a+C²s)/2",
    ], s))
    story.append(sp())
    story.append(Paragraph("<b>Common Pitfalls:</b>", s['body_bold']))
    pitfalls = [
        "Using ρ = λ/μ for M/M/c: WRONG. Must use ρ = λ/(cμ) for stability check and formulas.",
        "Forgetting units: ensure λ and μ are in SAME units (both per minute, or both per hour).",
        "In M/G/1: mixing up E[S²] and (E[S])²: E[S²] = Var[S] + (E[S])², not just (E[S])².",
        "Using the wrong formula for Lq in M/G/1: must use P-K, NOT ρ²/(1−ρ) (that is M/M/1 only).",
        "For G/G/1 Kingman: C²a is CV of INTER-ARRIVAL TIME, not of arrival rate.",
        "Not verifying Little's Law — always cross-check L = λW and Lq = λWq.",
        "Simulation: forgetting to warm up — starting statistics from t=0 when system starts empty biases results.",
        "M/M/c: confusing 'offered load' a = λ/μ with 'per-server utilisation' ρ = a/c.",
    ]
    for p in pitfalls:
        story.append(Paragraph(f"• {p}", s['bullet']))
    story.append(sp(2))

    story.append(section_header("8.5  Extended Summary: Derivation Strategy for Any Model", s))
    story.append(sp())
    story.append(Paragraph(
        "Regardless of the model, follow these steps:", s['body']))
    steps_gen = [
        "Identify model from Kendall notation and given parameters.",
        "Check stability (ρ < 1). If not satisfied, state no steady-state exists.",
        "Calculate P0 using the normalisation condition (or formula).",
        "Calculate Lq using the model-specific formula (M/M/1: ρ²/(1−ρ); M/M/c: Erlang-C × ρ/(1−ρ); M/G/1: P-K).",
        "Use W = Wq + 1/μ; Lq = λ·Wq; L = Lq + ρ (or a for multi-server); W = L/λ.",
        "Verify: L = λW and Lq = λWq (Little's Law cross-check).",
        "For probabilities: Pn = (1−ρ)ρⁿ (M/M/1), or use C(c,a) for delay prob (M/M/c).",
    ]
    for i, st in enumerate(steps_gen, 1):
        story.append(Paragraph(f"<b>Step {i}:</b> {st}", s['bullet']))
    story.append(sp(2))

    story.append(section_header("8.6  Additional Solved Problems (Mixed Types)", s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 8.1 — M/M/1 Finite Buffer (M/M/1/K)",
        [
            "Problem: λ = 5/hr, μ = 8/hr, K = 3 (max 3 customers in system). Find P0, P3 (blocking), λ_eff, L.",
            "",
            "For M/M/1/K:  ρ = λ/μ = 5/8 = 0.625  (Note: stability condition different — system always stable!)",
            "",
            "Pn = [(1−ρ)·ρⁿ] / (1−ρ^(K+1))   for n = 0,1,...,K",
            "Denominator = 1 − ρ^(K+1) = 1 − (0.625)^4 = 1 − 0.1526 = 0.8474",
            "P0 = (1−0.625)/0.8474 = 0.375/0.8474 = 0.4426",
            "P1 = 0.4426 × 0.625 = 0.2766",
            "P2 = 0.4426 × 0.625² = 0.1729",
            "P3 = 0.4426 × 0.625³ = 0.1081  (blocking probability)",
            "Check: 0.4426+0.2766+0.1729+0.1081 = 1.0002 ≈ 1 ✔",
            "",
            "Effective arrival rate: λ_eff = λ(1 − P3) = 5(1−0.1081) = 5 × 0.8919 = 4.460/hr",
            "L = Σ n·Pn = 0(0.4426) + 1(0.2766) + 2(0.1729) + 3(0.1081) = 0 + 0.2766 + 0.3458 + 0.3243 = 0.9467",
            "W = L/λ_eff = 0.9467/4.460 = 0.2122 hr = 12.7 min",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 8.2 — M/M/3 Queue",
        [
            "Problem: Call centre with λ = 10 calls/min, μ = 4 calls/min per agent, c = 3 agents.",
            "Find P0, delay prob, Lq, Wq.",
            "",
            "a = λ/μ = 10/4 = 2.5 Erlangs,   ρ = a/c = 2.5/3 = 0.8333 < 1 ✔",
            "",
            "P0 calculation:",
            "  Σ(k=0→2) a^k/k! = 1 + 2.5 + (2.5)²/2 = 1 + 2.5 + 3.125 = 6.625",
            "  Last term = a^3/(3!(1−ρ)) = (2.5)³/(6×0.1667) = 15.625/1.0 = 15.625",
            "  P0 = 1/(6.625 + 15.625) = 1/22.25 = 0.04494",
            "",
            "Erlang-C = C(3, 2.5) = 15.625 × P0 = 15.625 × 0.04494 = 0.7022",
            "(70.2% of arriving calls must wait — system is heavily loaded!)",
            "",
            "Lq = C(3,2.5) × ρ/(1−ρ) = 0.7022 × 0.8333/0.1667 = 0.7022 × 5.0 = 3.511 calls",
            "Wq = Lq/λ = 3.511/10 = 0.3511 min = 21.1 sec",
            "W  = Wq + 1/μ = 0.3511 + 0.25 = 0.6011 min = 36.1 sec",
            "L  = λW = 10 × 0.6011 = 6.011 calls",
        ], s))
    story.append(sp())

    story.append(example_box(
        "EXAMPLE 8.3 — Full M/G/1 Analysis with Hyperexponential Service",
        [
            "Problem: Web server with Poisson arrivals λ = 0.5 req/sec.",
            "Service: 80% of requests take Exp(2/sec), 20% take Exp(0.1/sec).",
            "(Hyperexponential H2 distribution)",
            "",
            "E[S] = 0.8×(1/2) + 0.2×(1/0.1) = 0.4 + 2.0 = 2.4 sec",
            "E[S²] = 0.8×(2/2²) + 0.2×(2/0.1²) = 0.8×0.5 + 0.2×200 = 0.4 + 40 = 40.4 sec²",
            "  [Note: for Exp(μ): E[S²] = 2/μ²]",
            "Var[S] = E[S²] − (E[S])² = 40.4 − (2.4)² = 40.4 − 5.76 = 34.64 sec²",
            "C²s = 34.64 / (2.4)² = 34.64/5.76 = 6.014  (very high variability!)",
            "",
            "ρ = λ·E[S] = 0.5 × 2.4 = 1.2  → UNSTABLE! ρ > 1",
            "System is overloaded — queue grows without bound.",
            "",
            "Fix: reduce λ to 0.3 req/sec:",
            "ρ = 0.3 × 2.4 = 0.72 < 1 ✔",
            "Wq = λ·E[S²]/(2(1−ρ)) = 0.3×40.4/(2×0.28) = 12.12/0.56 = 21.64 sec",
            "Lq = λ·Wq = 0.3×21.64 = 6.49 requests",
            "W  = 21.64 + 2.4 = 24.04 sec",
            "",
            "Compare with M/M/1 (same ρ=0.72): Lq(MM1) = 0.72²/0.28 = 1.851",
            "Hyperexponential gives Lq = 6.49 — about 3.5× worse due to high variability!",
        ], s))
    story.append(PageBreak())

    # ────────────────────────────────────────────────────────────────────────
    # APPENDIX / FORMULA CARD
    # ────────────────────────────────────────────────────────────────────────
    story.append(chapter_banner("APP", "APPENDIX — COMPLETE FORMULA CARD", s))
    story.append(sp(2))
    story.append(note_box(
        "This page is a self-contained formula card. Print or bookmark it for quick reference during revision.", s))
    story.append(sp())

    app_rows = [
        ["Little's Law", "L = λW,  Lq = λWq,  W = Wq + 1/μ,  L = Lq + ρ"],
        ["M/M/1 ρ", "ρ = λ/μ  (< 1 required)"],
        ["M/M/1 Pn", "P0 = 1−ρ,   Pn = (1−ρ)·ρⁿ"],
        ["M/M/1 L", "L = ρ/(1−ρ) = λ/(μ−λ)"],
        ["M/M/1 Lq", "Lq = ρ²/(1−ρ) = λ²/[μ(μ−λ)]"],
        ["M/M/1 W", "W = 1/(μ−λ)"],
        ["M/M/1 Wq", "Wq = ρ/(μ−λ) = λ/[μ(μ−λ)]"],
        ["M/M/1 P(Wq>t)", "ρ·e^{-(μ-λ)t}"],
        ["M/M/c ρ", "a = λ/μ,  ρ = a/c  (< 1 required)"],
        ["M/M/c P0", "[Σ(k=0→c-1) aᵏ/k!  +  aᶜ/(c!(1−ρ))]^{-1}"],
        ["Erlang-C", "C(c,a) = [aᶜ·P0] / [c!·(1−ρ)]"],
        ["M/M/c Lq", "Lq = C(c,a)·ρ/(1−ρ)"],
        ["M/M/c Wq", "Wq = Lq/λ = C(c,a)/(cμ−λ)"],
        ["M/G/1 ρ", "ρ = λ·E[S]  (< 1 required)"],
        ["M/G/1 E[S²]", "E[S²] = Var[S] + (E[S])²"],
        ["M/G/1 C²s", "C²s = Var[S]/(E[S])²"],
        ["M/G/1 Lq (P-K)", "Lq = ρ²(1+C²s)/(2(1−ρ)) = (ρ²+λ²Var[S])/(2(1−ρ))"],
        ["M/G/1 Wq (P-K)", "Wq = λ·E[S²]/(2(1−ρ))"],
        ["M/D/1 Lq", "Lq = ρ²/(2(1−ρ)) = (1/2)·Lq(M/M/1)"],
        ["G/G/1 C²a", "C²a = Var[A]·λ²  (CV² of inter-arrival time)"],
        ["G/G/1 Wq (Kingman)", "Wq ≈ (C²a+C²s)/2 · ρ/(1−ρ) · E[S]"],
        ["Exponential RVG", "X = −(1/λ)·ln(U),   U ~ Uniform(0,1)"],
        ["Simulation L", "L = (1/T)·Σ nᵢ·Δtᵢ  (time average)"],
        ["Stability (general)", "ρ = λ/(c·μ) < 1   for all models"],
    ]
    app_t = Table(
        [[Paragraph("<b>" + r[0] + "</b>", s['table_cell_left']),
          Paragraph(r[1], s['table_cell_left'])] for r in app_rows],
        colWidths=[5*cm, 11.7*cm]
    )
    app_t.setStyle(TableStyle([
        ('ROWBACKGROUNDS', (0,0), (-1,-1), [GOLD_BG, WHITE]),
        ('GRID', (0,0), (-1,-1), 0.5, GREY_MID),
        ('TOPPADDING', (0,0), (-1,-1), 5),
        ('BOTTOMPADDING', (0,0), (-1,-1), 5),
        ('LEFTPADDING', (0,0), (-1,-1), 7),
        ('RIGHTPADDING', (0,0), (-1,-1), 7),
        ('VALIGN', (0,0), (-1,-1), 'MIDDLE'),
        ('LINEABOVE', (0,0), (-1,0), 2, GOLD),
        ('LINEBELOW', (0,-1), (-1,-1), 2, GOLD),
    ]))
    story.append(app_t)
    story.append(sp(2))

    # back cover note
    back_data = [[
        Paragraph("END OF DOCUMENT", s['cover_sub']),
        Paragraph("All topics: Queueing Theory Foundations • M/M/1 • M/M/c • M/G/1 • G/G/1 • Simulation M/M/1 & M/M/2", s['cover_info']),
        Paragraph("Good luck on your final exam!", s['cover_title']),
    ]]
    back_t = Table(back_data, colWidths=[W - 4*cm])
    back_t.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,-1), DARK_BLUE),
        ('LEFTPADDING', (0,0), (-1,-1), 30),
        ('RIGHTPADDING', (0,0), (-1,-1), 30),
        ('TOPPADDING', (0,0), (-1,-1), 20),
        ('BOTTOMPADDING', (0,0), (-1,-1), 20),
        ('ALIGN', (0,0), (-1,-1), 'CENTER'),
    ]))
    story.append(back_t)

    doc.build(story)
    print(f"PDF saved to {path}")


build_pdf("/mnt/user-data/outputs/Queueing_Models_Final_Exam_Notes.pdf")