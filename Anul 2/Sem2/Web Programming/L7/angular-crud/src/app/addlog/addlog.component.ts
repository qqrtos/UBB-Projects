import { Component, OnInit } from '@angular/core';
import { Log } from '../log';
import { MainService } from '../main.service';

@Component({
  selector: 'app-addlog',
  templateUrl: './addlog.component.html',
  styleUrls: ['./addlog.component.css']
})
export class AddlogComponent implements OnInit {
  type: string;
  severity: string;
  date: Date;
  userId: number;
  text: string;

  constructor(private mainService: MainService) { }

  ngOnInit(): void {
  }

  addLog(): void {
    let log = new Log(null, this.type, this.severity, this.date, this.userId, this.text);
    this.mainService.addLog(log);
  }
}
