#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import re
import time
import random
import os
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.edge.service import Service
from selenium.webdriver.edge.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

# ----------------------------------------------------------------------
# 1. CONFIG
# ----------------------------------------------------------------------
CSV_FILE = "Hiring for Entrepreneurs Club (2025-26) - Working Committee.csv"
DRIVER_PATH = "/usr/local/bin/msedgedriver"
EDGE_PROFILE = os.path.expanduser("~/.config/microsoft-edge/WhatsAppBot")
HEADLESS = False
DRY_RUN = False          # <-- set True for a test run (no sending)

os.makedirs(EDGE_PROFILE, exist_ok=True)

# ----------------------------------------------------------------------
# 2. Load CSV & build message
# ----------------------------------------------------------------------
df = pd.read_csv(CSV_FILE)

def generate_message(row):
    name = row["Full Name"].strip()
    role = row["Roles currently Hiring for :"].strip()
    proof_col = "If yes, share your work proofs. (Drop the google drive link)"
    drive_link = ""

    # ---- experience mapping ------------------------------------------------
    exp_map = {
        "Video Editor": "Do you have any experience as a Video Editor?",
        "Graphic Designer": "Do you have any experience as a Graphic Designer?",
        "Content Writer": "Do you have any experience as a Content Writer?",
        "Web Developer": "Do you have any experience as a Web Developer?",
        "Marketing": "Do you have any experience in Marketing?",
        "Finance & Sponsorship Coordinator":
            "Do you have any prior experience in handling budgeting, sponsorship, or fundraising?",
    }
    exp_col = exp_map.get(role)
    if exp_col and pd.notna(row.get(exp_col)) and str(row[exp_col]).strip().lower() in {"yes","y"}:
        if pd.notna(row.get(proof_col)) and str(row[proof_col]).strip():
            drive_link = row[proof_col]

    # ---- special roles -----------------------------------------------------
    if role == "Reels Presenter / On-Camera Host":
        col = "Record and share a short (30–60 sec) video of yourself introducing a recent event, topic, or trend you like."
        if pd.notna(row.get(col)) and str(row[col]).strip():
            drive_link = row[col]
    if role == "Photographer / Videographer":
        col = "Share a few samples of your work (Google Drive link, Instagram, or any online portfolio)"
        if pd.notna(row.get(col)) and str(row[col]).strip():
            drive_link = row[col]

    enc = {
        "Web Developer": "Your technical skills are exactly what we need to build amazing digital experiences for our club!",
        "Content Writer": "Your creativity and way with words will help us communicate our mission effectively!",
        "Graphic Designer": "Your design skills will bring our club's vision to life visually!",
        "Video Editor": "Your editing skills will help us create engaging content for our audience!",
        "Marketing": "Your strategic mindset will help us reach new heights and engage more people!",
        "Photographer / Videographer": "Your eye for detail and storytelling will capture the essence of our events beautifully!",
        "Finance & Sponsorship Coordinator": "Your financial acumen will be crucial in securing resources for our initiatives!",
        "Reels Presenter / On-Camera Host": "Your confidence and charisma will make our social media presence shine!"
    }.get(role, "Your passion for this role is inspiring!")

    link_ack = f"\nWe've received your work sample here: {drive_link}" if drive_link else ""

    msg = f"""Hi {name},

Thank you for applying for the **{role}** role in the Entrepreneurs Club!
{enc}

We appreciate your interest and enthusiasm. Due to the ongoing semester exams, the hiring process will resume after the exams are over. We wish you the best of luck for your exams!

{link_ack}

Best regards,
Entrepreneurs Club Team
(Automated message from the President, Entrepreneurs Club)"""
    return msg.strip()

# ----------------------------------------------------------------------
# 3. Clean phone number
# ----------------------------------------------------------------------
def clean_phone(raw):
    digits = re.sub(r"\D", "", str(raw))
    if digits.startswith("91") and len(digits) == 12:
        return digits
    if len(digits) == 10:
        return "91" + digits
    if len(digits) > 10:
        digits = digits[-10:]
        return "91" + digits
    return digits

# ----------------------------------------------------------------------
# 4. Edge driver (keeps login)
# ----------------------------------------------------------------------
def setup_driver():
    opts = Options()
    opts.add_argument(f"--user-data-dir={EDGE_PROFILE}")
    opts.add_argument("--no-sandbox")
    opts.add_argument("--disable-dev-shm-usage")
    opts.add_argument("--disable-blink-features=AutomationControlled")
    opts.add_experimental_option("excludeSwitches", ["enable-automation"])
    opts.add_experimental_option('useAutomationExtension', False)
    opts.add_argument(
        "--user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 Edg/120.0.0.0"
    )
    if HEADLESS:
        opts.add_argument("--headless")
    service = Service(executable_path=DRIVER_PATH)
    driver = webdriver.Edge(service=service, options=opts)
    driver.execute_cdp_cmd("Page.addScriptToEvaluateOnNewDocument", {
        "source": "Object.defineProperty(navigator, 'webdriver', {get: () => undefined});"
    })
    driver.maximize_window()
    return driver

# ----------------------------------------------------------------------
# 5. Send ONE message – ONLY send_keys (no clipboard, no pop‑ups)
# ----------------------------------------------------------------------
def send_one(driver, phone: str, text: str) -> bool:
    if DRY_RUN:
        print(f"[DRY-RUN] +{phone}\n{text}\n{'-'*60}")
        return True

    # ---- open direct link -------------------------------------------------
    driver.get(f"https://web.whatsapp.com/send?phone={phone}")
    time.sleep(6)

    # ---- “Use WhatsApp Web” redirect (first run only) --------------------
    try:
        use_btn = WebDriverWait(driver, 8).until(
            EC.element_to_be_clickable(
                (By.XPATH, '//a[contains(@href,"web.whatsapp.com") and contains(.,"Use")]')
            )
        )
        driver.execute_script("arguments[0].click();", use_btn)
        print(f"  Clicked 'Use WhatsApp Web' for {phone}")
        time.sleep(5)
    except Exception:
        print(f"  No redirect popup for {phone}")

    # ---- wait for the real input box ------------------------------------
    wait = WebDriverWait(driver, 60)
    try:
        msg_box = wait.until(
            EC.presence_of_element_located(
                (By.XPATH, '//div[@contenteditable="true"][@data-tab="10"]')
            )
        )
        print(f"  Chat loaded for {phone}")
    except Exception:
        print(f"  Chat never loaded for {phone}")
        return False

    # ---- focus + clear ----------------------------------------------------
    driver.execute_script("arguments[0].scrollIntoView(true);", msg_box)
    driver.execute_script("arguments[0].click();", msg_box)
    time.sleep(0.5)
    msg_box.send_keys(Keys.CONTROL + "a")
    msg_box.send_keys(Keys.BACKSPACE)
    time.sleep(0.3)

    # ---- type line‑by‑line (human‑like) ----------------------------------
    for i, line in enumerate(text.split("\n")):
        msg_box.send_keys(line)
        if i < len(text.split("\n")) - 1:          # not the last line
            msg_box.send_keys(Keys.SHIFT + Keys.ENTER)
        time.sleep(random.uniform(0.03, 0.07))

    time.sleep(1)

    # ---- SEND -------------------------------------------------------------
    try:
        send_btn = WebDriverWait(driver, 6).until(
            EC.element_to_be_clickable((By.XPATH, '//button[@data-testid="compose-btn-send"]'))
        )
        driver.execute_script("arguments[0].click();", send_btn)
        print(f"  Sent to {phone}")
    except Exception:
        print("  Send button missing → pressing ENTER")
        msg_box.send_keys(Keys.ENTER)
        print(f"  Sent (ENTER) to {phone}")

    time.sleep(3)
    return True

# ----------------------------------------------------------------------
# 6. MAIN
# ----------------------------------------------------------------------
driver = setup_driver()
driver.get("https://web.whatsapp.com/")

# ---- login (profile keeps QR) -----------------------------------------
try:
    WebDriverWait(driver, 15).until(
        EC.presence_of_element_located((By.XPATH, '//div[@title="New chat" or @aria-label="New chat"]'))
    )
    print("Already logged in")
except Exception:
    input("\nScan the QR code now and press Enter...")
    try:
        WebDriverWait(driver, 60).until(
            EC.presence_of_element_located((By.XPATH, '//div[@title="New chat" or @aria-label="New chat"]'))
        )
        print("Login OK")
    except Exception:
        print("Login failed")
        driver.quit()
        exit(1)

sent = []
failed = []

for idx, row in df.iterrows():
    raw = row["Contact number (Preferably WhatsApp)"]
    phone = clean_phone(raw)

    if len(phone) != 12 or not phone.isdigit():
        print(f"Skip {row['Full Name']} – bad phone {raw}")
        failed.append((row["Full Name"], raw, "invalid"))
        continue

    msg = generate_message(row)
    print(f"\n{'='*60}")
    print(f"[{idx+1}/{len(df)}] {row['Full Name']} (+{phone})")
    print(f"{'='*60}")

    ok = send_one(driver, phone, msg)

    if ok:
        sent.append((row["Full Name"], phone))
        wait = random.uniform(14, 22)
        print(f"  Waiting {wait:.1f}s …")
        time.sleep(wait)
    else:
        failed.append((row["Full Name"], phone, "send,send_error"))
        time.sleep(5)

# ----------------------------------------------------------------------
# 7. Summary
# ----------------------------------------------------------------------
print("\n" + "="*60)
print(f"{len(sent)} sent")
for n, p in sent:
    print(f"  • {n} (+{p})")
print(f"\n{len(failed)} failed")
for n, p, r in failed:
    print(f"  • {n} (+{p}) – {r}")

driver.quit()
print("\nFinished!")