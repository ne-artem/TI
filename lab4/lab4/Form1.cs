using System;
using System.IO;
using System.Numerics;
using System.Text;
using System.Windows.Forms;

namespace lab4
{
    public partial class Form1 : Form
    {
        // Элементы управления GUI
        private TabControl tabControl;
        private TabPage tabSign, tabVerify;

        // Вкладка 1: Подписание
        private TextBox txtP, txtQ, txtD, txtE_Sign;
        private TextBox txtSourceHash, txtSignatureOutput;
        private Button btnSignFile;

        // Вкладка 2: Проверка (Только e и r)
        private TextBox txtE_Verify, txtR_Verify;
        private Button btnVerifyFile;

        // Общий лог (вынесен вниз формы)
        private TextBox txtLog;

        public Form1()
        {
            InitializeComponent();
            InitCustomComponents();
        }

        private void InitCustomComponents()
        {
            this.Text = "ЭЦП RSA — Вариант 1";
            this.Width = 620;
            this.Height = 600;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;

            // Инициализация TabControl
            tabControl = new TabControl { Left = 15, Top = 15, Width = 570, Height = 230 };
            tabSign = new TabPage { Text = "Создание подписи" };
            tabVerify = new TabPage { Text = "Проверка подписи" };

            // ==========================================
            // НАПОЛНЕНИЕ ВКЛАДКИ 1: ПОДПИСАНИЕ
            // ==========================================
            GroupBox gbKeysSign = new GroupBox { Text = "Параметры генерации ключей", Left = 10, Top = 10, Width = 540, Height = 80 };
            gbKeysSign.Controls.Add(new Label { Text = "p (простое):", Left = 10, Top = 20, Width = 80 });
            txtP = new TextBox { Left = 10, Top = 40, Width = 100, Text = "17" };

            gbKeysSign.Controls.Add(new Label { Text = "q (простое):", Left = 120, Top = 20, Width = 80 });
            txtQ = new TextBox { Left = 120, Top = 40, Width = 100, Text = "19" };

            gbKeysSign.Controls.Add(new Label { Text = "d (закрытый):", Left = 230, Top = 20, Width = 90 });
            txtD = new TextBox { Left = 230, Top = 40, Width = 100, Text = "67" };

            gbKeysSign.Controls.Add(new Label { Text = "e (открытый):", Left = 340, Top = 20, Width = 90 });
            txtE_Sign = new TextBox { Left = 340, Top = 40, Width = 180, ReadOnly = true, BackColor = System.Drawing.Color.LightGray };

            gbKeysSign.Controls.Add(txtP); gbKeysSign.Controls.Add(txtQ); gbKeysSign.Controls.Add(txtD); gbKeysSign.Controls.Add(txtE_Sign);
            tabSign.Controls.Add(gbKeysSign);

            GroupBox gbResults = new GroupBox { Text = "Результаты", Left = 10, Top = 95, Width = 540, Height = 95 };
            gbResults.Controls.Add(new Label { Text = "Хеш сообщения (10 с/сч):", Left = 10, Top = 20, Width = 150 });
            txtSourceHash = new TextBox { Left = 10, Top = 40, Width = 160, ReadOnly = true };

            gbResults.Controls.Add(new Label { Text = "Цифровая подпись (S):", Left = 180, Top = 20, Width = 140 });
            txtSignatureOutput = new TextBox { Left = 180, Top = 40, Width = 160, ReadOnly = true };

            btnSignFile = new Button { Text = "Подписать файл...", Left = 350, Top = 38, Width = 175, Height = 30 };
            btnSignFile.Click += BtnSignFile_Click;

            gbResults.Controls.Add(txtSourceHash); gbResults.Controls.Add(txtSignatureOutput); gbResults.Controls.Add(btnSignFile);
            tabSign.Controls.Add(gbResults);

            // ==========================================
            // НАПОЛНЕНИЕ ВКЛАДКИ 2: ПРОВЕРКА
            // ==========================================
            GroupBox gbKeysVerify = new GroupBox { Text = "Ввод открытых параметров (Ключ отправителя)", Left = 10, Top = 10, Width = 540, Height = 90 };
            gbKeysVerify.Controls.Add(new Label { Text = "Открытая экспонента (e):", Left = 15, Top = 30, Width = 160 });
            txtE_Verify = new TextBox { Left = 15, Top = 50, Width = 230, Text = "163" }; // Пример значения по умолчанию

            gbKeysVerify.Controls.Add(new Label { Text = "Модуль системы (r = p * q):", Left = 280, Top = 30, Width = 180 });
            txtR_Verify = new TextBox { Left = 280, Top = 50, Width = 230, Text = "323" }; // 17 * 19 = 323

            gbKeysVerify.Controls.Add(txtE_Verify); gbKeysVerify.Controls.Add(txtR_Verify);
            tabVerify.Controls.Add(gbKeysVerify);

            btnVerifyFile = new Button { Text = "Выбрать файл и проверить ЭЦП...", Left = 10, Top = 120, Width = 540, Height = 45 };
            btnVerifyFile.Click += BtnVerifyFile_Click;
            tabVerify.Controls.Add(btnVerifyFile);

            // Добавляем вкладки в TabControl
            tabControl.TabPages.Add(tabSign);
            tabControl.TabPages.Add(tabVerify);
            this.Controls.Add(tabControl);

            // ==========================================
            // ОБЩИЙ ЛОГ (Внизу формы)
            // ==========================================
            this.Controls.Add(new Label { Text = "Журнал проверок и вычисленных значений:", Left = 15, Top = 255, Width = 400 });
            txtLog = new TextBox { Left = 15, Top = 275, Width = 570, Height = 260, Multiline = true, ScrollBars = ScrollBars.Vertical, ReadOnly = true, Font = new System.Drawing.Font("Consolas", 9.5f) };
            this.Controls.Add(txtLog);

            // Привязка событий перерасчета e для первой вкладки
            txtP.TextChanged += (s, e) => RecalculateE();
            txtQ.TextChanged += (s, e) => RecalculateE();
            txtD.TextChanged += (s, e) => RecalculateE();
            RecalculateE();
        }

        #region Математическое ядро

        private BigInteger ModPow(BigInteger value, BigInteger exponent, BigInteger modulus)
        {
            if (modulus == 1) return 0;
            BigInteger result = 1;
            value = value % modulus;
            while (exponent > 0)
            {
                if (exponent % 2 == 1)
                    result = (result * value) % modulus;
                exponent >>= 1;
                value = (value * value) % modulus;
            }
            return result;
        }

        private BigInteger CalculateHash(string text, BigInteger r)
        {
            BigInteger h = 100;
            byte[] bytes = Encoding.UTF8.GetBytes(text);
            foreach (byte m in bytes)
            {
                h = ModPow(h + m, 2, r);
            }
            return h;
        }

        private BigInteger ModInverse(BigInteger e, BigInteger phi)
        {
            BigInteger m0 = phi, t, q;
            BigInteger x0 = 0, x1 = 1;
            if (phi == 1) return 0;
            while (e > 1)
            {
                q = e / phi; t = phi;
                phi = e % phi; e = t;
                t = x0; x0 = x1 - q * x0; x1 = t;
            }
            if (x1 < 0) x1 += m0;
            return x1;
        }

        private bool IsPrime(BigInteger n, int k = 10)
        {
            if (n <= 1 || n == 4) return false;
            if (n <= 3) return true;
            if (n % 2 == 0) return false;
            BigInteger d = n - 1;
            while (d % 2 == 0) d /= 2;
            Random rand = new Random();
            for (int i = 0; i < k; i++)
            {
                byte[] bytes = new byte[n.ToByteArray().LongLength];
                rand.NextBytes(bytes);
                BigInteger a = new BigInteger(bytes);
                if (a < 2) a = 2;
                if (a >= n - 2) a = n - 2;
                if (MillerRabinTest(a, d, n)) return false;
            }
            return true;
        }

        private bool MillerRabinTest(BigInteger a, BigInteger d, BigInteger n)
        {
            BigInteger x = ModPow(a, d, n);
            if (x == 1 || x == n - 1) return false;
            while (d != n - 1)
            {
                x = (x * x) % n;
                d *= 2;
                if (x == 1) return true;
                if (x == n - 1) return false;
            }
            return true;
        }

        #endregion

        #region Валидация

        // Проверка для вкладки подписания (Нужно всё)
        private bool ValidateSignInputs(out BigInteger p, out BigInteger q, out BigInteger d, out BigInteger r, out BigInteger phi)
        {
            p = 0; q = 0; d = 0; r = 0; phi = 0;

            if (!BigInteger.TryParse(txtP.Text, out p) || !IsPrime(p))
            {
                MessageBox.Show("Значение 'p' должно быть простым!", "Ошибка ввода", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            if (!BigInteger.TryParse(txtQ.Text, out q) || !IsPrime(q))
            {
                MessageBox.Show("Значение 'q' должно быть простым!", "Ошибка ввода", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            if (p == q)
            {
                MessageBox.Show("p и q не должны быть равны!", "Ошибка валидации", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }

            r = p * q;
            phi = (p - 1) * (q - 1);

            if (!BigInteger.TryParse(txtD.Text, out d) || d <= 1 || d >= phi || BigInteger.GreatestCommonDivisor(d, phi) != 1)
            {
                MessageBox.Show($"Закрытый ключ 'd' должен быть взаимно прост с φ(r) = {phi} и лежать в (1, φ(r))!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            return true;
        }

        // Проверка для вкладки верификации (Нужны только e и r!)
        private bool ValidateVerifyInputs(out BigInteger eKey, out BigInteger r)
        {
            eKey = 0; r = 0;

            if (!BigInteger.TryParse(txtE_Verify.Text, out eKey) || eKey <= 1)
            {
                MessageBox.Show("Введите корректное число для открытой экспоненты 'e'!", "Ошибка ввода", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            if (!BigInteger.TryParse(txtR_Verify.Text, out r) || r <= 1)
            {
                MessageBox.Show("Введите корректное число для модуля системы 'r'!", "Ошибка ввода", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            return true;
        }

        private void RecalculateE()
        {
            if (BigInteger.TryParse(txtP.Text, out BigInteger p) && IsPrime(p) &&
                BigInteger.TryParse(txtQ.Text, out BigInteger q) && IsPrime(q) && p != q)
            {
                BigInteger phi = (p - 1) * (q - 1);
                if (BigInteger.TryParse(txtD.Text, out BigInteger d) && d > 1 && d < phi && BigInteger.GreatestCommonDivisor(d, phi) == 1)
                {
                    BigInteger eKey = ModInverse(d, phi);
                    txtE_Sign.Text = eKey.ToString();

                    // Для удобства дублируем вычисленные параметры на вкладку проверки
                    txtE_Verify.Text = eKey.ToString();
                    txtR_Verify.Text = (p * q).ToString();
                    return;
                }
            }
            txtE_Sign.Text = "Ожидание верных p, q, d...";
        }

        #endregion

        #region Кнопки управления

        // ДЕЙСТВИЕ: ПОДПИСАТЬ ФАЙЛ
        private void BtnSignFile_Click(object sender, EventArgs e)
        {
            if (!ValidateSignInputs(out BigInteger p, out BigInteger q, out BigInteger d, out BigInteger r, out BigInteger phi))
                return;

            OpenFileDialog ofd = new OpenFileDialog { Filter = "Текстовые файлы (*.txt)|*.txt" };
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    string originalText = File.ReadAllText(ofd.FileName, Encoding.UTF8);
                    BigInteger hash = CalculateHash(originalText, r);
                    txtSourceHash.Text = hash.ToString();

                    BigInteger signature = ModPow(hash, d, r);
                    txtSignatureOutput.Text = signature.ToString();

                    string signedContent = originalText + "\r\n" + signature.ToString();

                    SaveFileDialog sfd = new SaveFileDialog { Filter = "Текстовые файлы (*.txt)|*.txt", FileName = Path.GetFileNameWithoutExtension(ofd.FileName) + "_signed.txt" };
                    if (sfd.ShowDialog() == DialogResult.OK)
                    {
                        File.WriteAllText(sfd.FileName, signedContent, Encoding.UTF8);

                        txtLog.AppendText($"[ПОДПИСЬ] Создана для файла: {Path.GetFileName(ofd.FileName)}\r\n");
                        txtLog.AppendText($"Используемые модули: r = {r}, d = {d}\r\n");
                        txtLog.AppendText($"Вычисленный Хэш: {hash}, Подпись S = {signature}\r\n");
                        txtLog.AppendText("--------------------------------------------------\r\n");
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка: {ex.Message}", "Ошибка файла", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        // ДЕЙСТВИЕ: ПРОВЕРИТЬ ФАЙЛ (Зависит ТОЛЬКО от e и r)
        private void BtnVerifyFile_Click(object sender, EventArgs e)
        {
            if (!ValidateVerifyInputs(out BigInteger eKey, out BigInteger r))
                return;

            OpenFileDialog ofd = new OpenFileDialog { Filter = "Текстовые файлы (*.txt)|*.txt" };
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    string[] lines = File.ReadAllLines(ofd.FileName, Encoding.UTF8);
                    if (lines.Length < 2)
                    {
                        if (lines.Length == 1 && BigInteger.TryParse(lines[0].Trim(), out BigInteger singleSig))
                            lines = new string[] { "", lines[0] };
                        else
                        {
                            MessageBox.Show("Некорректный формат или подпись отсутствует!", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            return;
                        }
                    }

                    string sigPart = lines[lines.Length - 1].Trim();
                    string messageText = string.Join("\r\n", lines, 0, lines.Length - 1);

                    if (!BigInteger.TryParse(sigPart, out BigInteger receivedSignature))
                    {
                        MessageBox.Show("Цифровая подпись в конце файла не распознана!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }

                    if (receivedSignature >= r)
                    {
                        txtLog.AppendText($"[ОШИБКА] Значение подписи S ({receivedSignature}) >= r ({r}).\r\n");
                        MessageBox.Show("ЭЦП Неверна! Компоненты нарушены.", "Результат", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }

                    // 1. Считаем хэш по тексту
                    BigInteger computedHash = CalculateHash(messageText, r);
                    // 2. Дешифруем хэш из подписи с помощью открытых e и r
                    BigInteger decryptedHash = ModPow(receivedSignature, eKey, r);

                    txtLog.AppendText($"[ПРОВЕРКА] Файл: {Path.GetFileName(ofd.FileName)}\r\n");
                    txtLog.AppendText($"Ключи проверки: e = {eKey}, r = {r}\r\n");
                    txtLog.AppendText($"Хэш из подписи (S^e mod r): {decryptedHash}\r\n");
                    txtLog.AppendText($"Хэш вычисленный:            {computedHash}\r\n");

                    if (computedHash == decryptedHash)
                    {
                        txtLog.AppendText("[РЕЗУЛЬТАТ] ЭЦП ВЕРНА. (Проверено только по e и r)\r\n");
                        txtLog.AppendText("--------------------------------------------------\r\n");
                        MessageBox.Show("Электронная цифровая подпись ВЕРНА!", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else
                    {
                        txtLog.AppendText("[РЕЗУЛЬТАТ] ЭЦП НЕВЕРНА! Данные изменены.\r\n");
                        txtLog.AppendText("--------------------------------------------------\r\n");
                        MessageBox.Show("Внимание! ЭЦП НЕВЕРНА!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка проверки: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        #endregion
    }
}