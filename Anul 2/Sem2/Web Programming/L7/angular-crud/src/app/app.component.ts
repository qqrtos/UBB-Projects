import { Component } from '@angular/core';
import { AddlogComponent } from './addlog/addlog.component';
import { MainService } from './main.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  providers: [MainService]
})
export class AppComponent {
  title = 'angular-crud';
}
