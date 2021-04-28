import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-addlog',
  templateUrl: './addlog.component.html',
  styleUrls: ['./addlog.component.css']
})
export class AddlogComponent implements OnInit {
  logType: string;

  constructor() { }

  ngOnInit(): void {
  }

  async addLog(): Promise<void> {

  }
}
