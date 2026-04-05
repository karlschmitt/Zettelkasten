

## 🔑 1. Generate an SSH key

Open your terminal and run:

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

👉 If your system doesn’t support `ed25519`, use:

```bash
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```

When prompted:

- Press **Enter** to accept the default file location

- Optionally set a **passphrase** (recommended)

---

## 📂 2. Start the SSH agent

```bash
eval "$(ssh-agent -s)"
```

Add your key:

```bash
ssh-add ~/.ssh/id_ed25519
```

---

## 📋 3. Copy your public key

```bash
cat ~/.ssh/id_ed25519.pub
```

Copy the full output (it starts with `ssh-ed25519`).

---

## 🌐 4. Add the key to GitHub

1. Go to GitHub

2. Click your profile → **Settings**
   
   1. Important follow the white rabbit: https://github.com/settings/keys

3. Go to **SSH and GPG keys**

4. Click **New SSH key**

5. Paste your key and give it a name (e.g. *My Laptop*)

---

## 🔌 5. Test the connection

```bash
ssh -T git@github.com
```

You should see:

```
Hi <username>! You've successfully authenticated...
```

---

## 🚀 6. Use SSH for your repo

When cloning a repo, use the SSH URL:

```bash
git clone git@github.com:username/repository.git
```

If your repo already exists locally, switch it:

```bash
git remote set-url origin git@github.com:username/repository.git
```

---

## ✅ Done!

Now you can push:

```bash
git push
