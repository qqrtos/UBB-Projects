
namespace WinFormsApp_Example {
    partial class Form1 {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.shipsGridView = new System.Windows.Forms.DataGridView();
            this.piratesGridView = new System.Windows.Forms.DataGridView();
            this.buttonSave = new System.Windows.Forms.Button();
            this.ShipsLabel = new System.Windows.Forms.Label();
            this.PiratesLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.shipsGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.piratesGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // shipsGridView
            // 
            this.shipsGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.shipsGridView.Location = new System.Drawing.Point(38, 61);
            this.shipsGridView.Name = "shipsGridView";
            this.shipsGridView.RowTemplate.Height = 25;
            this.shipsGridView.Size = new System.Drawing.Size(288, 179);
            this.shipsGridView.TabIndex = 0;
            // 
            // piratesGridView
            // 
            this.piratesGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.piratesGridView.Location = new System.Drawing.Point(376, 61);
            this.piratesGridView.Name = "piratesGridView";
            this.piratesGridView.RowTemplate.Height = 25;
            this.piratesGridView.Size = new System.Drawing.Size(309, 179);
            this.piratesGridView.TabIndex = 1;
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(160, 272);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(387, 59);
            this.buttonSave.TabIndex = 2;
            this.buttonSave.Text = "Save";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // ShipsLabel
            // 
            this.ShipsLabel.AutoSize = true;
            this.ShipsLabel.Location = new System.Drawing.Point(141, 33);
            this.ShipsLabel.Name = "ShipsLabel";
            this.ShipsLabel.Size = new System.Drawing.Size(35, 15);
            this.ShipsLabel.TabIndex = 3;
            this.ShipsLabel.Text = "Ships";
            // 
            // PiratesLabel
            // 
            this.PiratesLabel.AutoSize = true;
            this.PiratesLabel.Location = new System.Drawing.Point(512, 33);
            this.PiratesLabel.Name = "PiratesLabel";
            this.PiratesLabel.Size = new System.Drawing.Size(42, 15);
            this.PiratesLabel.TabIndex = 4;
            this.PiratesLabel.Text = "Pirates";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(723, 365);
            this.Controls.Add(this.PiratesLabel);
            this.Controls.Add(this.ShipsLabel);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.piratesGridView);
            this.Controls.Add(this.shipsGridView);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.shipsGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.piratesGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView shipsGridView;
        private System.Windows.Forms.DataGridView piratesGridView;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Label ShipsLabel;
        private System.Windows.Forms.Label PiratesLabel;
    }
}

