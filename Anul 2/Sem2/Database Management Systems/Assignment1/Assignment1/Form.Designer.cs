
namespace Assignment1 {
    partial class Form {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.AlbumsDataGridView = new System.Windows.Forms.DataGridView();
            this.SongsDataGridView = new System.Windows.Forms.DataGridView();
            this.AlbumsLabel = new System.Windows.Forms.Label();
            this.SongsLabel = new System.Windows.Forms.Label();
            this.PersistChangesButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.AlbumsDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SongsDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // AlbumsDataGridView
            // 
            this.AlbumsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.AlbumsDataGridView.Location = new System.Drawing.Point(12, 247);
            this.AlbumsDataGridView.Name = "AlbumsDataGridView";
            this.AlbumsDataGridView.RowTemplate.Height = 28;
            this.AlbumsDataGridView.Size = new System.Drawing.Size(617, 305);
            this.AlbumsDataGridView.TabIndex = 0;
            // 
            // SongsDataGridView
            // 
            this.SongsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SongsDataGridView.Location = new System.Drawing.Point(661, 247);
            this.SongsDataGridView.Name = "SongsDataGridView";
            this.SongsDataGridView.RowTemplate.Height = 28;
            this.SongsDataGridView.Size = new System.Drawing.Size(507, 305);
            this.SongsDataGridView.TabIndex = 1;
            // 
            // AlbumsLabel
            // 
            this.AlbumsLabel.AutoSize = true;
            this.AlbumsLabel.Location = new System.Drawing.Point(255, 198);
            this.AlbumsLabel.Name = "AlbumsLabel";
            this.AlbumsLabel.Size = new System.Drawing.Size(62, 20);
            this.AlbumsLabel.TabIndex = 2;
            this.AlbumsLabel.Text = "Albums";
            // 
            // SongsLabel
            // 
            this.SongsLabel.AutoSize = true;
            this.SongsLabel.Location = new System.Drawing.Point(900, 198);
            this.SongsLabel.Name = "SongsLabel";
            this.SongsLabel.Size = new System.Drawing.Size(55, 20);
            this.SongsLabel.TabIndex = 3;
            this.SongsLabel.Text = "Songs";
            // 
            // PersistChangesButton
            // 
            this.PersistChangesButton.Location = new System.Drawing.Point(489, 92);
            this.PersistChangesButton.Name = "PersistChangesButton";
            this.PersistChangesButton.Size = new System.Drawing.Size(236, 40);
            this.PersistChangesButton.TabIndex = 4;
            this.PersistChangesButton.Text = "Persist Changes";
            this.PersistChangesButton.UseVisualStyleBackColor = true;
            this.PersistChangesButton.Click += new System.EventHandler(this.PersistChangesButton_Click);
            // 
            // Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1180, 564);
            this.Controls.Add(this.PersistChangesButton);
            this.Controls.Add(this.SongsLabel);
            this.Controls.Add(this.AlbumsLabel);
            this.Controls.Add(this.SongsDataGridView);
            this.Controls.Add(this.AlbumsDataGridView);
            this.Name = "Form";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form_Load);
            ((System.ComponentModel.ISupportInitialize)(this.AlbumsDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SongsDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView AlbumsDataGridView;
        private System.Windows.Forms.DataGridView SongsDataGridView;
        private System.Windows.Forms.Label AlbumsLabel;
        private System.Windows.Forms.Label SongsLabel;
        private System.Windows.Forms.Button PersistChangesButton;
    }
}

