
namespace Assignment1_v2._0 {
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
            this.AlbumsDataGridView = new System.Windows.Forms.DataGridView();
            this.SongsDataGridView = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.PersistChangesButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.AlbumsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SongsDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // AlbumsDataGridView
            // 
            this.AlbumsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.AlbumsDataGridView.Location = new System.Drawing.Point(12, 224);
            this.AlbumsDataGridView.Name = "AlbumsDataGridView";
            this.AlbumsDataGridView.RowTemplate.Height = 25;
            this.AlbumsDataGridView.Size = new System.Drawing.Size(593, 312);
            this.AlbumsDataGridView.TabIndex = 0;
            // 
            // SongsDataGridView
            // 
            this.SongsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SongsDataGridView.Location = new System.Drawing.Point(646, 224);
            this.SongsDataGridView.Name = "SongsDataGridView";
            this.SongsDataGridView.RowTemplate.Height = 25;
            this.SongsDataGridView.Size = new System.Drawing.Size(481, 312);
            this.SongsDataGridView.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label1.Location = new System.Drawing.Point(251, 179);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(75, 25);
            this.label1.TabIndex = 2;
            this.label1.Text = "Albums";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label2.Location = new System.Drawing.Point(860, 179);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 25);
            this.label2.TabIndex = 3;
            this.label2.Text = "Songs";
            // 
            // PersistChangesButton
            // 
            this.PersistChangesButton.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.PersistChangesButton.Location = new System.Drawing.Point(406, 53);
            this.PersistChangesButton.Name = "PersistChangesButton";
            this.PersistChangesButton.Size = new System.Drawing.Size(422, 59);
            this.PersistChangesButton.TabIndex = 4;
            this.PersistChangesButton.Text = "Persist Changes";
            this.PersistChangesButton.UseVisualStyleBackColor = true;
            this.PersistChangesButton.Click += new System.EventHandler(this.PersistChangesButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1139, 548);
            this.Controls.Add(this.PersistChangesButton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SongsDataGridView);
            this.Controls.Add(this.AlbumsDataGridView);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.AlbumsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SongsDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView AlbumsDataGridView;
        private System.Windows.Forms.DataGridView SongsDataGridView;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button PersistChangesButton;
    }
}

